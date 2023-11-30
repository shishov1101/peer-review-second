#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
public:
    Domain(string_view str) : domain_(str) {};

    bool operator==(const Domain& rhs) const {
        return this->domain_ == rhs.domain_;
    }

    bool IsSubDomain(const Domain& rhs) const {
        if (rhs.domain_.size() <= this->domain_.size()) {
            return equal(rhs.domain_.begin(), rhs.domain_.end(), this->domain_.begin());
        }

        return false;
    }

    string GetDomain() const {
        return domain_;
    }

private:
    string domain_;
};

class DomainChecker {
public:
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end) : forbidden_domains_(begin, end) {
        DomainsSort();
    }

    bool IsForbidden(const Domain& domain) const {
        if (forbidden_domains_.empty()) {
            return false;
        }

        auto iterator = upper_bound(forbidden_domains_.begin(), forbidden_domains_.end(), domain, [](const Domain& value, const Domain& rhs) {
            return value.GetDomain() < rhs.GetDomain();
        });

        if (iterator != forbidden_domains_.begin()) {
            return domain.IsSubDomain(*prev(iterator));
        }

        return false;
    }

private:
    void DomainsSort() {
        sort(forbidden_domains_.begin(), forbidden_domains_.end(), [](const Domain& lhs, const Domain& rhs) {
            return lhs.GetDomain() < rhs.GetDomain();
        });
        auto last = unique(forbidden_domains_.begin(), forbidden_domains_.end(), [](const Domain& lhs, const Domain& rhs) {
            return rhs.IsSubDomain(lhs);
        });

        forbidden_domains_.erase(last, forbidden_domains_.end());
    }

    vector<Domain> forbidden_domains_;
};

template <typename Number>
vector<Domain> ReadDomains(istream& input, Number number) {
    vector<Domain> res;
    res.reserve(number);

    for (Number i = 0; i < number; ++i) {
        string domain;
        getline(input, domain);
        domain.insert(domain.begin(), '.');
        reverse(domain.begin(), domain.end());
        res.emplace_back(std::move(domain));
    }
    return res;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
