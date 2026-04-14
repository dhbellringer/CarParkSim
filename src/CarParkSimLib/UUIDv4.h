#include <array>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

class UUIDv4 {
public:
  static std::string generate() {
    // 16 random bytes
    std::array<unsigned char, 16> bytes{};

    // Use a good-quality RNG
    static thread_local std::random_device rd;
    static thread_local std::mt19937_64 gen(rd());
    static thread_local std::uniform_int_distribution<unsigned long long> dist;

    // Fill bytes using two 64?bit draws
    unsigned long long r1 = dist(gen);
    unsigned long long r2 = dist(gen);

    std::memcpy(bytes.data(), &r1, 8);
    std::memcpy(bytes.data() + 8, &r2, 8);

    // RFC 4122 compliance:
    // Set version (4) ? high nibble of byte 6
    bytes[6] = (bytes[6] & 0x0F) | 0x40;

    // Set variant (10xxxxxx) ? high bits of byte 8
    bytes[8] = (bytes[8] & 0x3F) | 0x80;

    // Convert to canonical string
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    for (size_t i = 0; i < bytes.size(); ++i) {
      oss << std::setw(2) << static_cast<int>(bytes[i]);
      if (i == 3 || i == 5 || i == 7 || i == 9)
        oss << "-";
    }

    return oss.str();
  }
};