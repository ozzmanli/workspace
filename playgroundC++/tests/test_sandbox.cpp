#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest.h"

// Reuse the class definitions straight from sandbox.cpp instead of
// duplicating them here. ATM_TESTING suppresses sandbox.cpp's own main()
// (see the #ifndef guard there) so this binary has exactly one main() -
// the one doctest generates for us above.
#define ATM_TESTING
#include "../sandbox.cpp"

TEST_CASE("ATM can be constructed and destroyed without crashing") {
    ATM myAtm;
    CHECK(true);  // reaching this line means construction/destruction didn't blow up
}

// --- The methods below are still empty stubs in sandbox.cpp. These test
// cases just confirm they can be called without crashing for now. As you
// implement each one for real, replace the CHECK with an actual assertion
// about the behavior (e.g. that a balance changed).

TEST_CASE("depositMoney runs without crashing (TODO: assert real behavior once implemented)") {
    ATM myAtm;
    myAtm.depositMoney(100);
    CHECK(true);
}

TEST_CASE("withdrawMoney runs without crashing (TODO: assert real behavior once implemented)") {
    ATM myAtm;
    myAtm.withdrawMoney(50);
    CHECK(true);
}

TEST_CASE("addUser + authentication: finds an existing user by name") {
    ATM myAtm;
    User petra("Petra", "1234", 100);
    User bjorn("Bjorn", "5678", 50);

    myAtm.addUser(petra);
    myAtm.addUser(bjorn);

    User lookup("Petra", "", 0);  // authentication() only compares by name
    User* found = myAtm.authentication(lookup);

    REQUIRE(found != nullptr);
    CHECK(found->getName() == "Petra");
}

TEST_CASE("authentication: returns nullptr when no user matches") {
    ATM myAtm;
    User petra("Petra", "1234", 100);
    myAtm.addUser(petra);

    User lookup("SomeoneElse", "", 0);
    User* found = myAtm.authentication(lookup);

    CHECK(found == nullptr);
}

TEST_CASE("User stores the name and pin it was constructed with") {
    User u("Kalle", "9999", 250);
    CHECK(u.getName() == "Kalle");
    CHECK(u.getPin() == "9999");
}
