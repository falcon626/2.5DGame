#pragma once

namespace Def // Only Constexpr Value
{
	constexpr Math::Color   Color = { 1.f,1.f,1.f,1.f};
	constexpr Math::Vector3 Vec   = { 0.f,0.f,0.f};
	constexpr Math::Matrix  Mat   = { 1.f, 0.f, 0.f, 0.f,
								      0.f, 1.f, 0.f, 0.f,
								      0.f, 0.f, 1.f, 0.f,
								      0.f, 0.f, 0.f, 1.f };
	
	constexpr auto SizTNull  = 0U;
	constexpr auto SizTOne   = 1U;

	constexpr auto IntNull   = 0;
	constexpr auto IntOne    = 1;

	constexpr auto FloatNull = 0.f;
	constexpr auto FloatOne  = 1.f;
}

/*
member m_memberValue

local localValue

argument = local

macro MACRO_NAME

bool isName

const ConstValue

class = const

enum = const

enum = const

struct = const

structMember memberValue_

matrix mMat

pointer
	share  sp
	unique up
	work   wp
*/