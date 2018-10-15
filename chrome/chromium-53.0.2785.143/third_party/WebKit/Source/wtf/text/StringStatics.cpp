/*
 * Copyright (C) 2010 Apple Inc. All Rights Reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "wtf/text/StringStatics.h"

#include "wtf/DynamicAnnotations.h"
#include "wtf/StaticConstructors.h"
#include "wtf/text/AtomicString.h"
#include "wtf/text/StringImpl.h"

namespace WTF {

StringImpl* StringImpl::empty()
{
    DEFINE_STATIC_LOCAL(StringImpl, emptyString, (ConstructEmptyString));
    WTF_ANNOTATE_BENIGN_RACE(&emptyString,
        "Benign race on the reference counter of a static string created by StringImpl::empty");
    return &emptyString;
}

StringImpl* StringImpl::empty16Bit()
{
    DEFINE_STATIC_LOCAL(StringImpl, emptyString, (ConstructEmptyString16Bit));
    WTF_ANNOTATE_BENIGN_RACE(&emptyString,
        "Benign race on the reference counter of a static string created by StringImpl::empty16Bit");
    return &emptyString;
}

WTF_EXPORT DEFINE_GLOBAL(AtomicString, nullAtom)
WTF_EXPORT DEFINE_GLOBAL(AtomicString, emptyAtom)
WTF_EXPORT DEFINE_GLOBAL(AtomicString, starAtom)
WTF_EXPORT DEFINE_GLOBAL(AtomicString, xmlAtom)
WTF_EXPORT DEFINE_GLOBAL(AtomicString, xmlnsAtom)
WTF_EXPORT DEFINE_GLOBAL(AtomicString, xlinkAtom)

// This is not an AtomicString because it is unlikely to be used as an
// event/element/attribute name, so it shouldn't pollute the AtomicString hash
// table.
WTF_EXPORT DEFINE_GLOBAL(String, xmlnsWithColon)

NEVER_INLINE unsigned StringImpl::hashSlowCase() const
{
    if (is8Bit())
        setHash(StringHasher::computeHashAndMaskTop8Bits(characters8(), m_length));
    else
        setHash(StringHasher::computeHashAndMaskTop8Bits(characters16(), m_length));
    return existingHash();
}

void AtomicString::init()
{
    ASSERT(isMainThread());

    new (NotNull, (void*)&nullAtom) AtomicString;
    new (NotNull, (void*)&emptyAtom) AtomicString("");
}

template<unsigned charactersCount>
PassRefPtr<StringImpl> addStaticASCIILiteral(const char (&characters)[charactersCount])
{
    unsigned length = charactersCount - 1;
    unsigned hash = StringHasher::computeHashAndMaskTop8Bits(reinterpret_cast<const LChar*>(characters), length);
    return adoptRef(StringImpl::createStatic(characters, length, hash));
}

void StringStatics::init()
{
    ASSERT(isMainThread());

    // FIXME: These should be allocated at compile time.
    new (NotNull, (void*)&starAtom) AtomicString("*");
    new (NotNull, (void*)&xmlAtom) AtomicString(addStaticASCIILiteral("xml"));
    new (NotNull, (void*)&xmlnsAtom) AtomicString(addStaticASCIILiteral("xmlns"));
    new (NotNull, (void*)&xlinkAtom) AtomicString(addStaticASCIILiteral("xlink"));
    new (NotNull, (void*)&xmlnsWithColon) String("xmlns:");
}

} // namespace WTF
