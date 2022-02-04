#include <string>

/**
 * \brief
 *
 * \tparam T
 */
template <class T> struct Result {
public:
    enum Status { Ok, Err };

    Result()
        : m_Status(Err)
        , m_Thing() {
    }

    Result(T resultValue)
        : m_Status(Ok)
        , m_Thing(resultValue) {
    }

    explicit Result(Status status, std::string err_msg = std::string())
        : m_Status(status)
        , m_Thing()
        , m_ErrorMessage(err_msg) {
    }

    // Explicit error with message
    static Result Error(std::string err_msg) {
        return Result(Err, err_msg);
    }

    // Implicit conversion to type T
    operator T() const {
        return m_Thing;
    }

    // Explicit conversion to type T
    T Value() const {
        return m_Thing;
    }

    Status GetStatus() const {
        return m_Status;
    }

    bool IsError() const {
        return m_Status == Err;
    }

    bool IsOk() const {
        return m_Status == Ok;
    }

    std::string ErrorMessage() const {
        return m_ErrorMessage;
    }

private:
    T m_Thing;
    Status m_Status;

    std::string m_ErrorMessage;
};
