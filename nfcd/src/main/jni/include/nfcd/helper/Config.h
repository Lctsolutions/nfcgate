#ifndef NFCD_CONFIG_H
#define NFCD_CONFIG_H

#include <vector>

using config_ref = std::unique_ptr<uint8_t>;

class Option {
public:
    Option(uint8_t type, uint8_t *value, uint8_t len)
            : mType(type), mLen(len), mValue(value) {

    }

    std::string name() const;

    uint8_t type() const {
        return mType;
    }

    uint8_t len() const {
        return mLen;
    }

    uint8_t *value() {
        return mValue;
    }

    void value(uint8_t *newValue, uint8_t newLen) {
        mValue = newValue;
        mLen = newLen;
    }

    void push(config_ref &config, uint8_t &offset);


protected:
    uint8_t mType, mLen;
    uint8_t *mValue;
};

class Config {
public:
    Config() = default;

    uint8_t total() const {
        return mTotal;
    }

    void add(uint8_t type, uint8_t *value, uint8_t len = 1) {
        mOptions.emplace_back(type, value, len);
    }

    void add(const Option &opt) {
        mOptions.push_back(opt);
    }

    void build(config_ref &config);
    void parse(uint8_t size, uint8_t *stream);

    std::vector<Option> &options() {
        return mOptions;
    }

protected:
    uint8_t mTotal = 0;
    std::vector<Option> mOptions;
};

#endif //NFCD_CONFIG_H
