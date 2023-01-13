#ifndef MCMAS_BENCHMARK_HH
#define MCMAS_BENCHMARK_HH

#include <sys/resource.h>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include "types.hh"

#ifdef BENCHMARK
#define BENCHMARK_INIT() benchmark_init();
#define BENCHMARK_START(name) benchmark_start(name);
#define BENCHMARK_END() benchmark_end();
#else
#define BENCHMARK_INIT() ;
#define BENCHMARK_START(name) ;
#define BENCHMARK_END() ;
#endif

struct benchmark_data_t
{
  struct timeval utime;
  struct timeval stime;
  struct timeval rtime;
};

struct benchmark_node_t
{
  benchmark_data_t data;
  benchmark_node_t *parent;
  map<string, benchmark_node_t *> children;
};

template <typename A, typename B>
string
concat(const A & a, const B & b) {
  stringstream s;
  s << a << b;
  return s.str();
}

void benchmark_init();
void benchmark_start(string benchmark_name);
void benchmark_end();
void benchmark_print();

ostream & operator<<(ostream & os, const struct timeval & tv);
ostream & operator<<(ostream & os, const struct benchmark_data_t & tv);

struct benchmark_data_t get_usage(void);

struct timeval timeval_subtract(const struct timeval *x,
    const struct timeval *y);
struct timeval timeval_add(const struct timeval *x,
    const struct timeval *y);
struct timeval timeval_zero();

struct benchmark_data_t benchmark_subtract(const struct benchmark_data_t *x,
    const struct benchmark_data_t *y);
struct benchmark_data_t benchmark_add(const struct benchmark_data_t *x,
    const struct benchmark_data_t *y);
struct benchmark_data_t benchmark_zero();

#endif // ! MCMAS_BENCHMARK_HH
