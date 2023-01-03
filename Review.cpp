//
// Created by david on 3.1.2023.
//

#include "Review.h"

Review::Review(char rating0, std::string comment0) : rating(rating0), comment(std::move(comment0)) {
    if (!(0 <= rating && rating <= 10)) {
        throw std::invalid_argument("Invalid rating value");
    }
    if (comment.length() > COMMENT_MAX_LENGTH) {
        throw std::length_error("Max comment length exceeded");
    }
}
