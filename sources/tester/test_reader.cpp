#include "test_reader.hpp"

//--------------------------------------------------------------------------------

#include "domain/file_reader.hpp"

//--------------------------------------------------------------------------------

test::TestReader::TestReader(const std::string& aTestPath,
                             int aTestCount) noexcept
    : mTestNum(1), mTestCount(aTestCount), mTestPath(aTestPath)
{
}

//--------------------------------------------------------------------------------

TestLibMessage
test::TestReader::getTest() noexcept
{
    TestLibMessage result;
    mMutex.lock();
    result.mTest = dom::FileReader::getAllData(
        mTestPath + std::to_string(mTestNum) + ".in");
    result.mAnswer = dom::FileReader::getAllData(
        mTestPath + std::to_string(mTestNum) + ".out");
    result.mTestNumber = mTestNum;
    mTestNum++;
    mMutex.unlock();
    return result;
}

//--------------------------------------------------------------------------------

bool
test::TestReader::hasTest() noexcept
{
    const std::lock_guard<std::mutex> lock(mMutex);
    return mTestNum <= mTestCount;
}

//--------------------------------------------------------------------------------