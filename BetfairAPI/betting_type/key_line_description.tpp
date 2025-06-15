namespace BetfairAPI::BettingType {
    template <typename Iterable>
    KeyLineDescription::KeyLineDescription(const Iterable& key_line)
        : key_line_(key_line.begin(),key_line.end()) {}
}