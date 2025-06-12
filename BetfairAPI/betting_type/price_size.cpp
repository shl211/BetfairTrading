#include "price_size.h"

namespace BetfairAPI::BettingType {
    PriceSize::PriceSize(double price, double size)
        : price_(price), size_(size) {};
        
    double PriceSize::getPrice() const {
        return price_; 
    }

    double PriceSize::getSize() const {
        return size_;
    }
}