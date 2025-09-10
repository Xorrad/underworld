#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.hpp"
#include "game/core/Includes.hpp"

// Desc: Tests related to the Item, ItemStack and Stockpile classes.

TEST_CASE("[stockpile] Contains") {

}

TEST_CASE("[stockpile] Contains") {
    Stockpile stockpile(20);
    UniquePtr<Item> type1 = MakeUnique<Item>("type1", "Type 1", 0, 1, 0);    
    
    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 1, 5));
    CHECK(stockpile.GetItems().size() == 1);
    CHECK(stockpile.Contains(type1->GetId(), 4));
    CHECK(stockpile.Contains(type1->GetId(), 5));
    CHECK_FALSE(stockpile.Contains(type1->GetId(), 6));
    CHECK_FALSE(stockpile.Contains("unknown type", 4));
}

TEST_CASE("[stockpile] Add Item") {
    Stockpile stockpile(20);
    UniquePtr<Item> type1 = MakeUnique<Item>("type1", "Type 1", 0, 1, 0);
    
    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 1, 5));
    CHECK(stockpile.GetVolume() == 5);
    CHECK(stockpile.GetItems().size() == 1);
    CHECK(stockpile.GetItems().begin()->second->GetType() == type1.get());
    CHECK(stockpile.GetItems().begin()->second->GetQuality() == 1);
    CHECK(stockpile.GetItems().begin()->second->GetQuantity() == 5);

    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 1, 4));
    CHECK(stockpile.GetVolume() == 9);
    CHECK(stockpile.GetItems().size() == 1);
    CHECK(stockpile.GetItems().begin()->second->GetType() == type1.get());
    CHECK(stockpile.GetItems().begin()->second->GetQuality() == 1);
    CHECK(stockpile.GetItems().begin()->second->GetQuantity() == 9);
}

TEST_CASE("[stockpile] Remove Item") {
    Stockpile stockpile(20);
    UniquePtr<Item> type1 = MakeUnique<Item>("type1", "Type 1", 0, 1, 0);
    
    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 1, 5));
    stockpile.RemoveItem(MakeUnique<ItemStack>(type1.get(), 1, 4));
    CHECK(stockpile.GetVolume() == 1);
    CHECK(stockpile.GetItems().size() == 1);
    CHECK(stockpile.GetItems().begin()->second->GetType() == type1.get());
    CHECK(stockpile.GetItems().begin()->second->GetQuality() == 1);
    CHECK(stockpile.GetItems().begin()->second->GetQuantity() == 1);
    
    stockpile.RemoveItem(MakeUnique<ItemStack>(type1.get(), 1, 1));
    CHECK(stockpile.GetVolume() == 0);
    CHECK(stockpile.GetItems().size() == 0);
}

TEST_CASE("[stockpile] Cached Volume") {
    Stockpile stockpile(20);
    UniquePtr<Item> type1 = MakeUnique<Item>("type1", "Type 1", 0, 1, 0);
    UniquePtr<Item> type2 = MakeUnique<Item>("type2", "Type 2", 0, 2, 0);

    CHECK(stockpile.GetMaxVolume() == 20);
    CHECK(stockpile.GetVolume() == 0);
    
    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 0, 1));
    CHECK(stockpile.GetVolume() == 1);
    
    stockpile.RemoveItem(MakeUnique<ItemStack>(type1.get(), 0, 1));
    CHECK(stockpile.GetVolume() == 0);

    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 0, 1));
    stockpile.AddItem(MakeUnique<ItemStack>(type2.get(), 0, 2));
    CHECK(stockpile.GetVolume() == 5);
}

TEST_CASE("[stockpile] Max Volume") {
    Stockpile stockpile(10);
    UniquePtr<Item> type1 = MakeUnique<Item>("type1", "Type 1", 0, 1, 0);

    CHECK(stockpile.GetMaxVolume() == 10);
    
    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 0, 9));
    CHECK(stockpile.GetVolume() == 9);
    
    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 0, 10));
    CHECK(stockpile.GetVolume() == 9);
    
    stockpile.AddItem(MakeUnique<ItemStack>(type1.get(), 0, 1));
    CHECK(stockpile.GetVolume() == 10);
}