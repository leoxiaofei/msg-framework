///boost/1_55_0/libs/iostreams/doc/index.html

#include <algorithm>                       // copy, min
#include <iosfwd>                          // streamsize
#include <boost/iostreams/categories.hpp>  // source_tag
#include <boost/iostreams/positioning.hpp>


namespace Msg
{
	using namespace boost::iostreams;

	template<typename Container>
	class container_device {
	public:
		typedef typename Container::value_type  char_type;
		typedef seekable_device_tag             category;

		container_device(Container& container)
			: container_(container), pos_(0)
		{ }


		std::streamsize read(char_type* s, std::streamsize n)
		{
			using namespace std;
			streamsize amt = static_cast<streamsize>(container_.size() - pos_);
			streamsize result = (min)(n, amt);
			if (result != 0) {
				std::copy(container_.begin() + (__w64 int)pos_,
					container_.begin() + (__w64 int)(pos_ + result),
					s);
				pos_ += result;
				return result;
			}
			else {
				return -1; // EOF
			}
		}

		std::streamsize write(const char_type* s, std::streamsize n)
		{
			using namespace std;
			streamsize result = 0;
			if (pos_ != container_.size()) {
				streamsize amt =
					static_cast<streamsize>(container_.size() - pos_);
				result = (min)(n, amt);
				std::copy(s, s + result, container_.begin() + (__w64 int)pos_);
				pos_ += result;
			}
			if (result < n) {
				container_.insert(container_.end(), s + result, s + n);
				pos_ = container_.size();
			}
			return n;
		}

		stream_offset seek(stream_offset off, std::ios_base::seekdir way)
		{
			using namespace std;

			// Determine new value of pos_
			stream_offset next;
			if (way == ios_base::beg) {
				next = off;
			}
			else if (way == ios_base::cur) {
				next = pos_ + off;
			}
			else if (way == ios_base::end) {
				next = container_.size() + off - 1;
			}
			else {
				throw ios_base::failure("bad seek direction");
			}

			// Check for errors
			if (next < 0 || next >= container_.size())
				throw ios_base::failure("bad seek offset");

			pos_ = next;
			return pos_;
		}

		Container& container() { return container_; }
	private:
		//typedef typename Container::size_type   size_type;
		Container&  container_;
		std::streamsize   pos_;
	};

}
