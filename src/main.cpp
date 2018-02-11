#include <gtest/gtest.h>
#include "../test/utAtom.h"
#include "../test/utNumber.h"
#include "../test/utVariable.h"
#include "../test/utStructure.h"
#include "../test/utTermFactory.h"
#include "../test/utPrologUtils.h"
#include "../test/utScanner.h"
#include "../test/utExp.h"
#include "../test/utExpBuilder.h"
#include "../test/utExpFactory.h"
#include "../test/utParser.h"
#include "../test/utOrExpIterator.h"
#include "../test/utClauseIterator.h"
#include "../inc/shell.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    // Shell shell;
    // shell.run();
    // return 0;
}
