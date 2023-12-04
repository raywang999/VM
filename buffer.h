
/*
 * abstraction over files and swap files
 * - read/write from/to swp files and real files into in-memory datastructure
 *  
 * public interface: 
 * - iterate through all characters in the buffer
 * - read/write from/to a specific line number
 * - insert/delete lines 
 * - insert/delete characters within a line
 */
template<typename char_type>
class lined_filebuf{
 public:
  void insert(size_t line, size_t ind, );
  virtual ~Buffer() =0;
};

inline Buffer::~Buffer(){}





