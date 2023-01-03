// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include <memory>
#include "gtest/gtest.h"

#include "Review.h"

using namespace ::testing;

TEST(TestReview, EmptyReview) {
    Review review;
    ASSERT_EQ(NO_RATING, review.getRating());
    ASSERT_EQ("", review.getComment());
}

TEST(TestReview, CreateReview) {
    Review review(9, "Som spokojny");
    ASSERT_EQ(9, review.getRating());
    ASSERT_EQ("Som spokojny", review.getComment());
}

TEST(TestReview, InvalidRating) {
    try {
        std::make_unique<Review>(11, "");
        ASSERT_TRUE(false);
    }
    catch (std::invalid_argument &) {

    }
}

TEST(TestReview, LongComment) {
    try {
        std::string longComment;
        longComment.resize(COMMENT_MAX_LENGTH + 1, 'A');
        std::make_unique<Review>(1, longComment);
        ASSERT_TRUE(false);
    }
    catch (std::length_error &) {
    }
}
