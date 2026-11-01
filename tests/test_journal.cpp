#include <gtest/gtest.h>
#include "GameJournal.hpp"
#include <fstream>
#include <cstdio>

TEST(GameJournalTest, AddAndRetrieveRecords) {
    GameJournal journal;
    journal.addRecord("100 на Красное", RouletteNumber(1), Money(200), Money(1100), Money(99900));
    
    ASSERT_EQ(journal.getRecords().size(), 1);
    EXPECT_EQ(journal.getRecords()[0].betInfo, "100 на Красное");
    EXPECT_EQ(journal.getRecords()[0].outcomeNumber, 1);
}

TEST(GameJournalTest, SaveAndLoadFromFile) {
    std::string testFilename = "test_journal.csv";
    GameJournal originalJournal;
    originalJournal.addRecord("50 на Зеро", RouletteNumber(0), Money(0), Money(500), Money(10050));
    
    EXPECT_NO_THROW(originalJournal.saveToFile(testFilename));

    GameJournal loadedJournal;
    EXPECT_NO_THROW(loadedJournal.loadFromFile(testFilename));

    ASSERT_EQ(loadedJournal.getRecords().size(), 1);
    EXPECT_EQ(loadedJournal.getRecords()[0].betInfo, "50 на Зеро");
    EXPECT_EQ(loadedJournal.getRecords()[0].outcomeNumber, 0);
    EXPECT_EQ(loadedJournal.getRecords()[0].playerBalance, 500);

    std::remove(testFilename.c_str());
}