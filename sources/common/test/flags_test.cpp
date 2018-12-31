#include <cstdint>
#include <catch2/catch.hpp>

#include <sidekick/utility/flags.h>

using namespace sidekick;

namespace
{

enum MyEnums : std::uint16_t
{
    ZERO  = 0b0000,
    ONE   = 0b0001,
    TWO   = 0b0010,
    THREE = 0b0100,
    FOUR  = 0b1000
};

} // anonymous namespace

template <>
struct sidekick::enable_bit_flags_for_enum<MyEnums>
{
    using type = std::uint64_t;
};

static_assert(std::is_same_v<bit_flags<MyEnums>::value_type,
                             std::uint64_t>,
              "enable_bit_flags_for_enum not working correctly");

TEST_CASE("Default initialization is zero", "[bit_flags]")
{
    bit_flags<MyEnums> flags;

    REQUIRE(flags == ZERO);
    REQUIRE(ZERO == flags);
    REQUIRE(!flags);
}

TEST_CASE("Initialize with enum", "[bit_flags]")
{
    bit_flags<MyEnums> flags{ONE};

    REQUIRE(flags == ONE);
    REQUIRE(ONE == flags);
    REQUIRE(flags);
}

TEST_CASE("Initialize with raw value", "[bit_flags]")
{
    bit_flags<MyEnums> flags{0x01};

    REQUIRE(flags.bits == 0x01);
    REQUIRE(flags);
}

TEST_CASE("OR bit_flags with enum", "[bit_flags]")
{
    bit_flags<MyEnums> flags0{ONE};
    flags0 |= TWO;

    bit_flags<MyEnums> flags1{THREE};
    flags1 = flags1 | FOUR;
    flags1 = FOUR | flags1;


    REQUIRE(flags0.bits == 0x3);
    REQUIRE(flags1.bits == 0xc);
    REQUIRE((flags0 | flags1).bits == 0xf);
}

TEST_CASE("AND bit_flags with enum", "[bit_flags]")
{
    bit_flags<MyEnums> flags0{ONE | TWO | THREE};

    auto flags1 = flags0;
    flags1 &= TWO;
    REQUIRE(flags1 == TWO);

    auto flags2 = flags0 & flags1;
    REQUIRE(flags2 == TWO);


    auto flags3 = flags0 & (ONE | TWO);
    REQUIRE((flags3 & ONE));
    REQUIRE((flags3 & TWO));
}

TEST_CASE("XOR bit_flags with enum", "[bit_flags]")
{
    bit_flags<MyEnums> flags0{ONE | THREE};

    flags0 ^= TWO;
    REQUIRE(flags0 == (ONE | TWO | THREE));

    REQUIRE((flags0 ^ ONE ^ TWO) == THREE);
}

