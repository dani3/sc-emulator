#include <string>

/**
 * \brief Wrapper class around an object inspired by Rust's Result struct. This class is intended
 * to be used across the code base instead of exceptions.
 *
 * The `Result` object can be unwrapped to get the internal value.
 */
template <class T> struct Result {
public:
    enum Status { Ok, Err };

    /**
     * \brief Default constructor implemented to avoid compilation errors.
     *
     * \note It should not be used.
     */
    Result()
        : m_Status(Err)
        , m_Thing() {
    }

    /**
     * \brief Construct a new Result object containing a valid object.
     */
    Result(T resultValue)
        : m_Status(Ok)
        , m_Thing(resultValue) {
    }

    /**
     * \brief Construct a new Result object.
     *
     * \param status  Status enum.
     * \param err_msg Error message.
     */
    explicit Result(Status status, std::string err_msg = std::string())
        : m_Status(status)
        , m_Thing()
        , m_ErrorMessage(err_msg) {
    }

    /**
     * \brief Explicit error with message.
     */
    static Result Error(std::string err_msg) {
        return Result(Err, err_msg);
    }

    /**
     * \brief Implicit conversion to type T.
     */
    operator T() const {
        return m_Thing;
    }

    /**
     * \brief Explicit conversion to type T.
     */
    T Value() const {
        return m_Thing;
    }

    /**
     * \brief Get the underlying object.
     *
     * \todo Should this panic?
     */
    Status GetStatus() const {
        return m_Status;
    }

    /**
     * \brief Return true if the result is an Error.
     *
     * \return true if the result is an Error, false otherwise.
     */
    bool IsError() const {
        return m_Status == Err;
    }

    /**
     * \brief Return true if the result is Ok and contains an obect.
     *
     * \return true if the result is Ok and contains an obect, false otherwise.
     */
    bool IsOk() const {
        return m_Status == Ok;
    }

    /**
     * \brief Return the error message.
     */
    std::string ErrorMessage() const {
        return m_ErrorMessage;
    }

private:
    // Underlying object.
    T m_Thing;
    // Status of the Result.
    Status m_Status;

    std::string m_ErrorMessage;
};
