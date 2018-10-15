// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "TestInterfaceOrLong.h"

#include "bindings/core/v8/ToV8.h"
#include "bindings/core/v8/V8TestInterface.h"
#include "bindings/tests/idls/core/TestImplements2.h"
#include "bindings/tests/idls/core/TestImplements3Implementation.h"
#include "bindings/tests/idls/core/TestInterfacePartial.h"
#include "bindings/tests/idls/core/TestInterfacePartial2Implementation.h"

namespace blink {

TestInterfaceOrLong::TestInterfaceOrLong()
    : m_type(SpecificTypeNone)
{
}

TestInterfaceImplementation* TestInterfaceOrLong::getAsTestInterface() const
{
    ASSERT(isTestInterface());
    return m_testInterface;
}

void TestInterfaceOrLong::setTestInterface(TestInterfaceImplementation* value)
{
    ASSERT(isNull());
    m_testInterface = value;
    m_type = SpecificTypeTestInterface;
}

TestInterfaceOrLong TestInterfaceOrLong::fromTestInterface(TestInterfaceImplementation* value)
{
    TestInterfaceOrLong container;
    container.setTestInterface(value);
    return container;
}

int TestInterfaceOrLong::getAsLong() const
{
    ASSERT(isLong());
    return m_long;
}

void TestInterfaceOrLong::setLong(int value)
{
    ASSERT(isNull());
    m_long = value;
    m_type = SpecificTypeLong;
}

TestInterfaceOrLong TestInterfaceOrLong::fromLong(int value)
{
    TestInterfaceOrLong container;
    container.setLong(value);
    return container;
}

TestInterfaceOrLong::TestInterfaceOrLong(const TestInterfaceOrLong&) = default;
TestInterfaceOrLong::~TestInterfaceOrLong() = default;
TestInterfaceOrLong& TestInterfaceOrLong::operator=(const TestInterfaceOrLong&) = default;

DEFINE_TRACE(TestInterfaceOrLong)
{
    visitor->trace(m_testInterface);
}

void V8TestInterfaceOrLong::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, TestInterfaceOrLong& impl, UnionTypeConversionMode conversionMode, ExceptionState& exceptionState)
{
    if (v8Value.IsEmpty())
        return;

    if (conversionMode == UnionTypeConversionMode::Nullable && isUndefinedOrNull(v8Value))
        return;

    if (V8TestInterface::hasInstance(v8Value, isolate)) {
        TestInterfaceImplementation* cppValue = V8TestInterface::toImpl(v8::Local<v8::Object>::Cast(v8Value));
        impl.setTestInterface(cppValue);
        return;
    }

    if (v8Value->IsNumber()) {
        int cppValue = toInt32(isolate, v8Value, NormalConversion, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setLong(cppValue);
        return;
    }

    {
        int cppValue = toInt32(isolate, v8Value, NormalConversion, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setLong(cppValue);
        return;
    }

}

v8::Local<v8::Value> toV8(const TestInterfaceOrLong& impl, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    switch (impl.m_type) {
    case TestInterfaceOrLong::SpecificTypeNone:
        return v8::Null(isolate);
    case TestInterfaceOrLong::SpecificTypeTestInterface:
        return toV8(impl.getAsTestInterface(), creationContext, isolate);
    case TestInterfaceOrLong::SpecificTypeLong:
        return v8::Integer::New(isolate, impl.getAsLong());
    default:
        ASSERT_NOT_REACHED();
    }
    return v8::Local<v8::Value>();
}

TestInterfaceOrLong NativeValueTraits<TestInterfaceOrLong>::nativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState)
{
    TestInterfaceOrLong impl;
    V8TestInterfaceOrLong::toImpl(isolate, value, impl, UnionTypeConversionMode::NotNullable, exceptionState);
    return impl;
}

} // namespace blink
