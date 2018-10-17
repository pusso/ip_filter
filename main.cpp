#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <list>
#include <tuple>
#include <vector>

using namespace std;

unsigned int bytes_to_int( unsigned char &b0, unsigned char &b1, unsigned char &b2, unsigned char &b3 ) {
  bitset<32> binary = 0;
  binary |= bitset<32>(b0);
  binary = binary << 8;
  binary |= bitset<32>(b1);
  binary = binary << 8;
  binary |= bitset<32>(b2);
  binary = binary << 8;
  binary |= bitset<32>(b3);
  return binary.to_ulong();
}

tuple<unsigned int, string, bool, bool, bool> f(unsigned int number) {
  unsigned char b0 = (number >> 24) & 0xFF;
  unsigned char b1 = (number >> 16) & 0xFF;
  unsigned char b2 = (number >> 8) & 0xFF;
  unsigned char b3 = number & 0xFF;

  string ip_str =
    to_string(b0) + '.' +
    to_string(b1) + '.' +
    to_string(b2) + '.' +
    to_string(b3);

  bool task0 = false;
  bool task1 = false;
  bool task2 = false;

  const unsigned char char46 = char(46);
  const unsigned char char70 = char(70);

  task0 = (b0 == 1);
  task1 = ((b0 == char46) && (b1 == char70));
  task2 = ((b0 == char46) || (b1 == char46) || (b2 == char46) || (b3 == char46));

  return make_tuple(number, ip_str, task0, task1, task2);
}

int main() {
  struct reading {
    unsigned int b0;
    unsigned int b1;
    unsigned int b2;
    unsigned int b3;
  } read_tmp;

  struct ip_bytes {
    unsigned char b0 = 0;
    unsigned char b1 = 0;
    unsigned char b2 = 0;
    unsigned char b3 = 0;
  } ip_tmp;

  char ch_temp;
  short int i_temp;

  vector <tuple <unsigned int, string, bool, bool, bool>> v_ips;

  while (!cin.eof()) {
    read_tmp.b0 = 0; read_tmp.b1 = 0; read_tmp.b2 = 0; read_tmp.b3 = 0;
    cin >> read_tmp.b0 >> ch_temp >> read_tmp.b1 >> ch_temp >> read_tmp.b2 >> ch_temp >> read_tmp.b3 >> i_temp >> i_temp;
    ip_tmp.b0 = read_tmp.b0; ip_tmp.b1 = read_tmp.b1; ip_tmp.b2 = read_tmp.b2; ip_tmp.b3 = read_tmp.b3;

    if (!cin.fail()) {
      cout << read_tmp.b0 << "." << read_tmp.b1 << "." << read_tmp.b2 << "." << read_tmp.b3 <<  endl;
      v_ips.push_back(f(bytes_to_int(ip_tmp.b0, ip_tmp.b1, ip_tmp.b2, ip_tmp.b3)));
    }

  }

  sort( v_ips.begin(), v_ips.end(),
  [](const tuple<unsigned int, string, bool, bool, bool>& a,  const tuple<unsigned int, string, bool, bool, bool>& b) -> bool {
    return std::get<0>(a) > std::get<0>(b);
  });

  list<string> s_task0 = {};
  list<string> s_task1 = {};
  list<string> s_task2 = {};

  for (auto &v : v_ips) {
    if (get<2>(v)) {
      s_task0.push_back(get<1>(v));
    }

    if (get<3>(v)) {
      s_task1.push_back(get<1>(v));
    }

    if (get<4>(v)) {
      s_task2.push_back(get<1>(v));
    }
    cout << get<1>(v) << endl;
  }

//  cout << "-----------------" << endl ;
  for (auto &v : s_task0) {
    cout << v << endl;
  }
//  cout << "-----------------" << endl ;
  for (auto &v : s_task1) {
    cout << v << endl;
  }
//  cout << "-----------------" << endl ;
  for (auto &v : s_task2) {
    cout << v << endl;
  }

}