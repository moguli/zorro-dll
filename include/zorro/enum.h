
#ifndef ZORRO_ENUM_H_
#define ZORRO_ENUM_H_

#include "common.h"

#if ZORRO_CPP >= 11
#include <type_traits>
#define ZORRO_ENUM_UNDERLYING_TYPE(enumType) typename ::std::underlying_type<enumType>::type
#define ZORRO_OPEN_ENUM(name) \
	typedef enum class name {
#define ZORRO_OPEN_ENUM_TYPE(name, type) \
	typedef enum class name : type {
#define ZORRO_CLOSE_ENUM(name) \
	} name;
#else
namespace z {
template<typename EnumDef, typename UnderlyingType = typename EnumDef::TUnderlyingType>
class CEnum : public EnumDef
{
public:
	typedef UnderlyingType TUnderlyingType;
	typedef CEnum<EnumDef, UnderlyingType> TThis;

	CEnum() {}
	CEnum(TUnderlyingType value) : m_value(value) {}

	operator TUnderlyingType() const { return m_value; }

	friend bool operator == (const TThis& left, const TThis& right) { return left.m_value == right.m_value; }
	friend bool operator != (const TThis& left, const TThis& right) { return left.m_value != right.m_value; }
	friend bool operator <  (const TThis& left, const TThis& right) { return left.m_value <  right.m_value; }
	friend bool operator <= (const TThis& left, const TThis& right) { return left.m_value <= right.m_value; }
	friend bool operator >  (const TThis& left, const TThis& right) { return left.m_value >  right.m_value; }
	friend bool operator >= (const TThis& left, const TThis& right) { return left.m_value >= right.m_value; }

private:
	TUnderlyingType m_value;
};

template<typename UnderlyingType>
struct SEnumBaseDef
{
	typedef UnderlyingType TUnderlyingType;
};
} // namespace z
#define ZORRO_ENUM_UNDERLYING_TYPE(enumType) enumType::TUnderlyingType
#define ZORRO_OPEN_ENUM(name) \
	struct S##name##Def : public ::z::SEnumBaseDef<int> { \
		enum EnumType {
#define ZORRO_OPEN_ENUM_TYPE(name, type) \
	struct S##name##Def : public ::z::SEnumBaseDef<type> { \
		enum EnumType {
#define ZORRO_CLOSE_ENUM(name) \
		}; \
	}; \
	typedef ::z::CEnum<S##name##Def> name;
#endif

#define ZORRO_BUILD_ENUM_BIT_OPERATORS_WITH_TYPE(enumType, intType) \
	inline enumType operator & ( intType left, enumType right )  { return enumType(left & static_cast<intType>( right )); } \
	inline enumType operator | ( intType left, enumType right )  { return enumType(left & static_cast<intType>( right )); } \
	inline enumType operator & ( enumType left, intType right )  { return enumType(static_cast<intType>( left ) & right); } \
	inline enumType operator | ( enumType left, intType right )  { return enumType(static_cast<intType>( left ) & right); } \
	inline enumType operator & ( enumType left, enumType right ) { return enumType(static_cast<intType>( left ) & static_cast<intType>( right )); } \
	inline enumType operator | ( enumType left, enumType right ) { return enumType(static_cast<intType>( left ) | static_cast<intType>( right )); } \
	inline enumType operator ~ ( enumType value )                { return enumType(~static_cast<intType>( value )); } \

#define ZORRO_BUILD_ENUM_COMP_OPERATORS_WITH_TYPE(enumType, intType) \
	inline bool operator <  ( enumType left, intType right ) { return static_cast<intType>( left ) <  right;                         } \
	inline bool operator <  ( intType left, enumType right ) { return left                         <  static_cast<intType>( right ); } \
	inline bool operator <= ( enumType left, intType right ) { return static_cast<intType>( left ) <= right;                         } \
	inline bool operator <= ( intType left, enumType right ) { return left                         <= static_cast<intType>( right ); } \
	inline bool operator >  ( enumType left, intType right ) { return static_cast<intType>( left ) >  right;                         } \
	inline bool operator >  ( intType left, enumType right ) { return left                         >  static_cast<intType>( right ); } \
	inline bool operator >= ( enumType left, intType right ) { return static_cast<intType>( left ) >= right;                         } \
	inline bool operator >= ( intType left, enumType right ) { return left                         >= static_cast<intType>( right ); } \
	inline bool operator == ( enumType left, intType right ) { return static_cast<intType>( left ) == right;                         } \
	inline bool operator == ( intType left, enumType right ) { return left                         == static_cast<intType>( right ); } \
	inline bool operator != ( enumType left, intType right ) { return static_cast<intType>( left ) != right;                         } \
	inline bool operator != ( intType left, enumType right ) { return left                         != static_cast<intType>( right ); } \

#define ZORRO_BUILD_ENUM_BIT_OPERATORS(enumType) \
        ZORRO_BUILD_ENUM_BIT_OPERATORS_WITH_TYPE(enumType, ZORRO_ENUM_UNDERLYING_TYPE(enumType))

#define ZORRO_BUILD_ENUM_COMP_OPERATORS(enumType) \
        ZORRO_BUILD_ENUM_COMP_OPERATORS_WITH_TYPE(enumType, ZORRO_ENUM_UNDERLYING_TYPE(enumType))

#endif // ZORRO_ENUM_H_
