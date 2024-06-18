#pragma once

namespace Def // Only Constexpr Value
{
	constexpr Math::Color   Color = { 1.f,1.f,1.f,1.f};

	constexpr Math::Vector3 Vec   = { 0.f,0.f,0.f};

	constexpr Math::Matrix  Mat   = { 1.f, 0.f, 0.f, 0.f,
								      0.f, 1.f, 0.f, 0.f,
								      0.f, 0.f, 1.f, 0.f,
								      0.f, 0.f, 0.f, 1.f };

	constexpr auto IntNull   = 0;
	constexpr auto IntOne    = 1;

	constexpr auto LongNull  = 0L;
	constexpr auto LongOne   = 1L;
	
	constexpr auto SizTNull  = 0U;
	constexpr auto SizTOne   = 1U;

	constexpr auto FloatNull = 0.f;
	constexpr auto FloatOne  = 1.f;
}

/*
local        localValue

argument   = local

macro        MACRO_NAME

bool         isName

const        ConstValue

constexpr  = const

class      = const
	member   m_memberValue

namespace  = const
	menmber  _value 

enum       = const

enum class = const

struct       tagStruct
	member   memberValue_

union        _tagUnion

matrix       mMat

pointer
	raw      p
	share    sp
	unique   up
	work     wp

function   = const
	lambda = local   

priority
 matrix = bool = local = member < constexpr = const < argument < pointer

.h   This Extension Has    Cpp And Classes
.hpp This Extension Has No Cpp
.hxx This Extension Has No Cpp And Classes
*/