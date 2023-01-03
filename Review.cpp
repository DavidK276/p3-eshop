//
// Created by david on 3.1.2023.
//

#include "Review.h"

Review::Review(char rating0, std::string comment0) : rating(rating0), comment(std::move(comment0)) {}
