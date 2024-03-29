#include "frequency-dictionary.hpp"

#include <fstream>

const size_t DEFAULT_SIZE = 98299; // Рандомное простое число.

FrequencyDictionary::FrequencyDictionary():
  size_(DEFAULT_SIZE),
  count_(0),
  data_(new DoubleLinkedList[DEFAULT_SIZE])
{}

FrequencyDictionary::FrequencyDictionary(size_t size)
{
  if (size == 0)
  {
    throw (std::invalid_argument("Размер хеш таблицы должен быть положительным числом!"));
  }
  size_ = size;
  count_ = 0;
  data_ = new DoubleLinkedList[size];
}

FrequencyDictionary::~FrequencyDictionary()
{
  delete[] data_;
}

void FrequencyDictionary::insertWord(const std::string& str)
{
  std::string word = str; // Слово, которое непосредственно будем добавлять.
  if (isWord(word)) // Проверяем на соответствие слову.
  {
    toLower(word); // Переводим слово в нижний регистр.
    // Одновременно добавляем элемент в таблицу
    // и проверяем, произошло добавление или просто увеличение счетчика.
    if (data_[hashByDivision(word, size_)].insertItem(word))
    {
      count_++;
    }
  }
  else
  {
    throw (std::invalid_argument("Некооректное слово!"));
  }
}

size_t FrequencyDictionary::searchWord(const std::string& str) const
{
  if (isWord(str))
  {
    // Ищем значение по ключу str в сответствующем двусвязном списке.
    // Если слова в хеш таблице нет - просто получим 0.
    return data_[hashByDivision(str, size_)].searchItem(str);
  }
  else
  {
    throw(std::invalid_argument("Некорректное слово!"));
  }
}

bool FrequencyDictionary::deleteWord(const std::string& str)
{
  if (isWord(str))
  {
    // Одновременно производим попытку удаления
    // и уменьшение счетчика, если удаление произошло.
    if (data_[hashByDivision(str, size_)].deleteItem(str))
    {
      count_--;
      return true;
    }
  }
  else
  {
    throw(std::invalid_argument("Некорректное слово!"));
  }
  return false;
}

void FrequencyDictionary::readFile(const std::string& fileName)
{
  std::ifstream fin(fileName);
  if (!fin)
  {
    throw(std::runtime_error("Ошибка открытия файла!"));
  }

  std::string str = "";
  while (!fin.eof())
  {
    fin >> str; // Считываем очередную строку из файла.
    clearWord(str); // Очищаем строку от не букв.
    try
    {
      insertWord(str);
    }
    catch (const std::invalid_argument& error) // Пропускаем ошибки о некорректных словах (пропускаем эти слова).
    {}
  }
  fin.close();
}

void FrequencyDictionary::printUnsorted(std::ostream& out) const
{
  for (size_t i = 0; i < size_; i++)
  {
    data_[i].print(out);
  }
}

void FrequencyDictionary::fillVector(std::vector < std::pair< std::string, size_t > > &vec) const
{
  vec.clear();
  for (size_t i = 0; i < size_; i++)
  {
    data_[i].fillVector(vec);
  }
}

void FrequencyDictionary::printSorted(std::ostream &out) const
{
  std::vector< std::pair< std::string, size_t > > vec;
  fillVector(vec);
  quickSort(vec, 0, vec.size() - 1);
  printVector(vec, out);
}

std::vector< std::pair< std::string, size_t > > FrequencyDictionary::getThreeMost() const
{
  std::vector< std::pair< std::string, size_t > > vec;
  std::pair< std::string, size_t > emptyPair;
  emptyPair.first = "";
  emptyPair.second = 0;
  for (size_t i = 0; i < 3; i++) // Заполняем созданный вектор тремя пустыми парами.
  {
    vec.push_back(emptyPair);
  }

  for (size_t i = 0; i < size_; i++) // Заполняем вектор трех чаще всего встречающихся слов.
  {
    data_[i].fillThreeMost(vec);
  }

  return vec;
}

void FrequencyDictionary::printThreeMost(std::ostream& out) const
{
  std::vector< std::pair< std::string, size_t > > vec = getThreeMost();
  printVector(vec, out);
}

void FrequencyDictionary::clear()
{
  for (size_t i = 0; i < size_; i++)
  {
    data_[i].clear(); // Очищаем каждый двусвязный список хеш-таблицы.
  }
  count_ = 0; // Не забываем обнулить количество слов в словаре.
}

size_t FrequencyDictionary::size()
{
  return size_;
}

size_t FrequencyDictionary::count()
{
  return count_;
}

size_t FrequencyDictionary::collisions()
{
  size_t result = 0;
  for (size_t i = 0; i < size_; i++)
  {
    if (data_[i].count() > 1) // Если в двусвязном списке больше 1 слова - это коллизия.
    {
      result++;
    }
  }
  return result;
}
