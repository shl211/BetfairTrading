#include "price_size.h"
#include "math_utils.hpp"

namespace BetfairAPI::BettingType {
    PriceSize::PriceSize(double price, double size)
        : price_(price), size_(size) {};
        
    bool PriceSize::operator==(const PriceSize& other) const {
        return BetfairAPI::Utils::almostEqual(price_,other.price_) &&
            BetfairAPI::Utils::almostEqual(size_,other.size_);
    }

    bool PriceSize::operator!=(const PriceSize& other) const {
        return !(*this == other);
    }

    double PriceSize::getPrice() const {
        return price_; 
    }

    double PriceSize::getSize() const {
        return size_;
    }
}