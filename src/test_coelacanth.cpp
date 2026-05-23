#include <catch2/catch_test_macros.hpp>

#include "coelacanth_types.hpp"
#include "machine/ticker/ticker_machine.hpp"

INITIALIZE_EASYLOGGINGPP

TEST_CASE("ticker machine toggles between tock and tick") {
    Coelacanth::TickerMachine ticker;

    REQUIRE(ticker.is_tock());
    ticker.tick();
    REQUIRE(ticker.is_tick());
    ticker.tick();
    REQUIRE(ticker.is_tock());
}
