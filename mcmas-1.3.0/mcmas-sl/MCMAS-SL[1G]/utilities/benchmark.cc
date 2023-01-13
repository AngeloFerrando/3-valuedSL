#include "benchmark.hh"


benchmark_node_t *current_benchmark;
pthread_mutex_t *benchmark_mutex;


void
benchmark_init()
{
  benchmark_mutex = new pthread_mutex_t();
  pthread_mutex_init(benchmark_mutex, NULL);

  benchmark_data_t zero = benchmark_zero();
  benchmark_data_t usage = get_usage();

  current_benchmark = new benchmark_node_t();
  current_benchmark->data = benchmark_subtract(&zero, &usage);
  current_benchmark->parent = NULL;

  atexit(benchmark_print);
}


void
benchmark_start(string benchmark_name)
{
  pthread_mutex_lock(benchmark_mutex);

  map<string, benchmark_node_t *> & children = current_benchmark->children;

  map<string, benchmark_node_t *>::iterator it = children.find(benchmark_name);
  if (it == children.end()) {
    benchmark_node_t *subcurrent_benchmark = new benchmark_node_t();
    subcurrent_benchmark->data = benchmark_zero();
    subcurrent_benchmark->parent = current_benchmark;
    it = children.insert(make_pair(benchmark_name, subcurrent_benchmark)).first;
  }
  current_benchmark = it->second;

  struct benchmark_data_t usage = get_usage();
  current_benchmark->data = benchmark_subtract(
      &current_benchmark->data, &usage);

  pthread_mutex_unlock(benchmark_mutex);
}


void
benchmark_end()
{
  pthread_mutex_lock(benchmark_mutex);

  struct benchmark_data_t current = get_usage();
  current_benchmark->data = benchmark_add(&current_benchmark->data, &current);
  current_benchmark = current_benchmark->parent;

  pthread_mutex_unlock(benchmark_mutex);
}


void
benchmark_traverse(string label, string indent, benchmark_node_t *node,
                   vector<vector<string> > *table)
{
  vector<string> row;

  // Label
  row.push_back(indent + label);

  // Real time
  stringstream real_stream;
  real_stream << node->data.rtime;
  row.push_back(real_stream.str());

  // Total time
  stringstream total_stream;
  total_stream << timeval_add(&node->data.utime, &node->data.stime);
  row.push_back(total_stream.str());

  // User time
  stringstream user_stream;
  user_stream << node->data.utime;
  row.push_back(user_stream.str());

  // System time
  stringstream system_stream;
  system_stream << node->data.stime;
  row.push_back(system_stream.str());

  table->push_back(row);

  benchmark_data_t total = benchmark_zero();

  for (map<string, benchmark_node_t*>::iterator it = node->children.begin();
       it != node->children.end(); it++) {
    total = benchmark_add(&total, &it->second->data);
    benchmark_traverse(it->first, indent + "  |  ", it->second, table);
  }

  // Rest
  if (node->children.size() > 0) {
    benchmark_node_t *rest_node = new benchmark_node_t();
    rest_node->data = benchmark_subtract(&node->data, &total);
    benchmark_traverse("<rest>", indent + "  +- ", rest_node, table);
  }

  delete node;
}


void
benchmark_print()
{
  if (options["quiet"] == 0) {
    benchmark_data_t usage = get_usage();
    current_benchmark->data = benchmark_add(&usage, &current_benchmark->data);

    cout << "====== BENCHMARK ======" << endl;

    vector<vector<string> > table;

    vector<string> labels;
    labels.push_back("CODE");
    labels.push_back("REAL");
    labels.push_back("CPU");
    labels.push_back("USER");
    labels.push_back("SYSTEM");
    table.push_back(labels);

    benchmark_traverse("mcmas-total", "", current_benchmark, &table);

    vector<size_t> lengths(table.begin()->size(), 0);
    for (vector<vector<string> >::iterator it = table.begin();
         it != table.end(); it++) {
      for (size_t i = 0; i < it->size(); i++) {
        lengths[i] = max(lengths[i], (*it)[i].size());
      }
    }

    for (vector<vector<string> >::iterator it = table.begin();
         it != table.end(); it++) {
      for (size_t i = 0; i < it->size(); i++) {
        if (i == 0) {
          cout << left;
        } else {
          cout << "  " << right;
        }
        cout << setw(lengths[i]) << setfill(' ') << (*it)[i];
      }
      cout << endl;
    }
  }

  current_benchmark = NULL;

  pthread_mutex_destroy(benchmark_mutex);
  delete benchmark_mutex;
  benchmark_mutex = NULL;
}


ostream &
operator<<(ostream & os, const struct timeval & tv)
{
  return os << tv.tv_sec << "." << setfill('0') << setw(6) << tv.tv_usec;
}


ostream &
operator<<(ostream & os, const struct benchmark_data_t & t)
{
  return os << "[USER: " << t.utime << ", SYSTEM: " << t.stime << ", TOTAL: "
            << timeval_add(&t.utime, &t.stime) << "]";
}


struct benchmark_data_t
get_usage()
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);

  struct timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  struct timeval rtime;
  rtime.tv_sec = spec.tv_sec;
  rtime.tv_usec = spec.tv_nsec / 1000;

  struct benchmark_data_t data;
  data.utime = usage.ru_utime;
  data.stime = usage.ru_stime;
  data.rtime = rtime;

  return data;
}


struct timeval
timeval_subtract(const struct timeval *x, const struct timeval *y)
{
  struct timeval result;

  result.tv_sec = x->tv_sec - y->tv_sec;
  result.tv_usec = x->tv_usec - y->tv_usec;

  if (result.tv_usec < 0) {
    result.tv_usec += 1000000;
    result.tv_sec -= 1;
  } else if (result.tv_usec >= 1000000) {
    result.tv_usec -= 1000000;
    result.tv_sec += 1;
  }

  return result;
}


struct timeval
timeval_add(const struct timeval *x, const struct timeval *y)
{
  struct timeval negative_y;
  negative_y.tv_sec = -y->tv_sec;
  negative_y.tv_usec = -y->tv_usec;

  return timeval_subtract(x, &negative_y);
}


struct timeval
timeval_zero()
{
  struct timeval t;
  t.tv_sec = 0;
  t.tv_usec = 0;
  return t;
}


struct benchmark_data_t
benchmark_subtract(const struct benchmark_data_t *x,
                   const struct benchmark_data_t *y)
{
  struct benchmark_data_t result;
  result.utime = timeval_subtract(&x->utime, &y->utime);
  result.stime = timeval_subtract(&x->stime, &y->stime);
  result.rtime = timeval_subtract(&x->rtime, &y->rtime);
  return result;
}


struct benchmark_data_t
benchmark_add(const struct benchmark_data_t *x,
              const struct benchmark_data_t *y)
{
  struct benchmark_data_t result;
  result.utime = timeval_add(&x->utime, &y->utime);
  result.stime = timeval_add(&x->stime, &y->stime);
  result.rtime = timeval_add(&x->rtime, &y->rtime);
  return result;
}


struct benchmark_data_t
benchmark_zero()
{
  struct benchmark_data_t result;
  result.utime = timeval_zero();
  result.stime = timeval_zero();
  result.rtime = timeval_zero();
  return result;
}
