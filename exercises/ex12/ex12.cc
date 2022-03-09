/*
 * Copyright ©2022 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <ctime>

#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;
static int NUM_THREADS = 3;
static constexpr int kNumSnacks = 6;
static SimpleQueue queue;
static unsigned int seed = time(nullptr);
static pthread_mutex_t write_lock;
struct thd_arg {
  string name;
};
// Thread safe print that prints the given str on a line
void thread_safe_print(const string& str) {
  pthread_mutex_lock(&write_lock);
  // Only one thread can hold the lock at a time, making it safe to
  // use cout. If we didn't lock before using cout, the order of things
  // put into the stream could be mixed up.
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

// Produces kNumSnacks snacks of the given type
// You should NOT modify this method at all
void producer(const string& snack_type) {
  for (int i = 0; i < kNumSnacks; i++) {
    queue.Enqueue(snack_type);
    thread_safe_print(snack_type + " ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

// Eats 2 * kNumSnacks snacks
// You should NOT modify this method at all
void consumer() {
  for (int i = 0; i < kNumSnacks * 2; i++) {
    bool successful = false;
    string snack_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        // Sleep for a bit and then check again
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&snack_type);
    }
    thread_safe_print(snack_type + " eaten!");
  }
}
void* producer_cover(void* arg) {
  struct thd_arg* a = reinterpret_cast<struct thd_arg*>(arg);
  producer(a->name);
  return nullptr;
}
void* consume_cover(void* arg) {
  consumer();
  return nullptr;
}


int main(int argc, char** argv) {
  // Your task: Make the two producers and the single consumer
  // all run concurrently (hint: use pthreads)
  // producer("Nian gao");
  // producer("Tangyuan");
  // consumer();

  // pthread_mutex_destroy(&write_lock);
  // return EXIT_SUCCESS;



  pthread_t thds[3];  // array of thread ids
  pthread_mutex_init(&write_lock, nullptr);
  // create threads to run thread_main()
  // for (int i = 0; i < NUM_THREADS; i++) {
    struct thd_arg* args1 = new struct thd_arg;
    args1->name = "Nian gao";
    // args->num = LOOP_NUM;
    if (pthread_create(&thds[0], nullptr, &producer_cover, args1) != 0) {
      std::cerr << "pthread_create failed" << endl;
    }

    struct thd_arg* args2 = new struct thd_arg;
    args2->name = "Tangyuan";
    // args->num = LOOP_NUM;
    if (pthread_create(&thds[1], nullptr, &producer_cover, args2) != 0) {
      std::cerr << "pthread_create failed" << endl;
    }
    struct thd_arg* args3 = new struct thd_arg;
    // args->num = LOOP_NUM;
    if (pthread_create(&thds[2], nullptr, &consume_cover, nullptr) != 0) {
      std::cerr << "pthread_create failed" << endl;
    }
    
  //}

  // wait for all child threads to finish
  // (children may terminate out of order, but cleans up in order)
  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(thds[i], nullptr) != 0) {
      std::cerr << "pthread_join failed" << endl;
    }
  }

  // print out the final sum (expecting NUM_THREADS * LOOP_NUM)
  // cout << "Total: " << sum_total << endl;

  pthread_mutex_destroy(&write_lock);  // destroy the mutex to clean up
  return EXIT_SUCCESS;
}
