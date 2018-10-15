#!/usr/bin/python
#
# Copyright (C) 2009 Google Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Copyright (c) 2009 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Generate aggregate .cpp files that include multiple V8 binding .cpp files.

This can be a single output file, to preserve symbol space; or multiple output
files, to reduce maximum compilation unit size and allow parallel compilation.

Usage:
aggregate_generated_bindings.py COMPONENT_DIR IDL_FILES_LIST -- OUTPUT_FILE1 OUTPUT_FILE2 ...

COMPONENT_DIR is the relative directory of a component, e.g., 'core', 'modules'.
IDL_FILES_LIST is a text file containing the IDL file paths, so the command
line doesn't exceed OS length limits.
OUTPUT_FILE1 etc. are filenames of output files.

Design doc: http://www.chromium.org/developers/design-documents/idl-build
"""

import errno
import os
import re
import sys

from utilities import should_generate_impl_file_from_idl, get_file_contents, idl_filename_to_component, idl_filename_to_interface_name, read_idl_files_list_from_file

COPYRIGHT_TEMPLATE = """/*
 * THIS FILE WAS AUTOMATICALLY GENERATED, DO NOT EDIT.
 *
 * This file was generated by the action_derivedsourcesallinone.py script.
 *
 * Copyright (C) 2009 Google Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
"""


def extract_meta_data(file_paths):
    """Extracts interface name from each IDL file."""
    meta_data_list = []

    for file_path in file_paths:
        if not file_path.endswith('.idl'):
            print 'WARNING: non-IDL file passed: "%s"' % file_path
            continue
        if not os.path.exists(file_path):
            print 'WARNING: file not found: "%s"' % file_path
            continue

        idl_file_contents = get_file_contents(file_path)
        if not should_generate_impl_file_from_idl(idl_file_contents):
            continue

        # Extract interface name from file name
        interface_name = idl_filename_to_interface_name(file_path)

        meta_data = {
            'name': interface_name,
        }
        meta_data_list.append(meta_data)

    return meta_data_list


def generate_content(component_dir, aggregate_partial_interfaces, files_meta_data_this_partition):
    # Add fixed content.
    output = [COPYRIGHT_TEMPLATE,
              '#define NO_IMPLICIT_ATOMICSTRING\n\n']

    # List all includes.
    files_meta_data_this_partition.sort()
    for meta_data in files_meta_data_this_partition:
        if aggregate_partial_interfaces:
            cpp_filename = 'V8%sPartial.cpp' % meta_data['name']
        else:
            cpp_filename = 'V8%s.cpp' % meta_data['name']

        output.append('#include "bindings/%s/v8/%s"\n' %
                      (component_dir, cpp_filename))

    return ''.join(output)


def write_content(content, output_file_name):
    parent_path, file_name = os.path.split(output_file_name)
    if not os.path.exists(parent_path):
        print 'Creating directory: %s' % parent_path
        os.makedirs(parent_path)
    with open(output_file_name, 'w') as f:
        f.write(content)


def main(args):
    if len(args) <= 4:
        raise Exception('Expected at least 5 arguments.')
    component_dir = args[1]
    input_file_name = args[2]
    in_out_break_index = args.index('--')
    output_file_names = args[in_out_break_index + 1:]

    idl_file_names = read_idl_files_list_from_file(input_file_name,
                                                   is_gyp_format=True)
    components = set([idl_filename_to_component(filename)
                      for filename in idl_file_names])
    if len(components) != 1:
        raise Exception('Cannot aggregate generated codes in different components')
    aggregate_partial_interfaces = component_dir not in components

    files_meta_data = extract_meta_data(idl_file_names)
    total_partitions = len(output_file_names)
    for partition, file_name in enumerate(output_file_names):
        files_meta_data_this_partition = [
                meta_data for meta_data in files_meta_data
                if hash(meta_data['name']) % total_partitions == partition]
        file_contents = generate_content(component_dir,
                                         aggregate_partial_interfaces,
                                         files_meta_data_this_partition)
        write_content(file_contents, file_name)


if __name__ == '__main__':
    sys.exit(main(sys.argv))
