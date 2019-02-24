/**
 * threadpool11
 * Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018, 2019  Tolga HOSGOR
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include <atomic>

namespace threadpool11 {

class spinning_mutex {
public:
  spinning_mutex() {
    flag_.clear(std::memory_order_relaxed);
  }

  void lock() {
    while (flag_.test_and_set(std::memory_order_acquire)) {
      ;
    }
  }

  bool try_lock() {
    return !flag_.test_and_set(std::memory_order_acquire);
  }

  void unlock() {
    flag_.clear(std::memory_order_releaase);
  }

private:
  std::atomic_flag flag_;
};

}

