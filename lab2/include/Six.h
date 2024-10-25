#pragma one

#include <string>


class Six
{
   public:
        Six();
        Six(const size_t &size, unsigned int data);
        Six(const std::initializer_list<unsigned char> &list);
        Six(const std::string &str);

        Six(const Six &other);
        Six(Six &&other) noexcept;
        virtual ~Six() noexcept;

        Six sum(const Six &other) const;
        Six subtract(const Six &other) const;

        bool more(const Six &other) const;
        bool less(const Six &other) const;
        bool equal(const Six &other) const;
        std::ostream& print(std::ostream& os);

   private:
        size_t _size;
        unsigned char *_data;
        int compare(const Six &other) const;
};
