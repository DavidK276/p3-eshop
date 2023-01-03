//
// Created by david on 3.1.2023.
//

#ifndef ESHOP_REVIEW_H
#define ESHOP_REVIEW_H

#include <iostream>

#define COMMENT_MAX_LENGTH 240
#define NO_RATING (-1)

class Review {
protected:
    char rating = NO_RATING;
    std::string comment;
public:
    Review() = default;

    virtual ~Review() = default;

    Review(char rating0, std::string comment0);

    char getRating() const { return this->rating; };

    const std::string &getComment() const { return this->comment; };
};


#endif //ESHOP_REVIEW_H
