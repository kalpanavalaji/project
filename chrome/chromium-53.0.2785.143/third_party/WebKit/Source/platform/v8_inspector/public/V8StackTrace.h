// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8StackTrace_h
#define V8StackTrace_h

#include "platform/inspector_protocol/Platform.h"
#include "platform/inspector_protocol/String16.h"
#include "platform/v8_inspector/protocol/Runtime.h"

#include <v8.h>

namespace blink {

// TODO(dgozman): migrate to V8SourceLocation.
class V8StackTrace {
public:
    virtual bool isEmpty() const = 0;
    virtual String16 topSourceURL() const = 0;
    virtual int topLineNumber() const = 0;
    virtual int topColumnNumber() const = 0;
    virtual String16 topScriptId() const = 0;
    virtual String16 topFunctionName() const = 0;

    virtual ~V8StackTrace() { }
    virtual std::unique_ptr<protocol::Runtime::StackTrace> buildInspectorObject() const = 0;
    virtual String16 toString() const = 0;
    virtual std::unique_ptr<V8StackTrace> clone() = 0;
    virtual std::unique_ptr<V8StackTrace> isolatedCopy() = 0; // Safe to pass between threads.
};

} // namespace blink

#endif // V8StackTrace_h
