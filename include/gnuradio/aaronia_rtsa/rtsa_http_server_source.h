/* -*- c++ -*- */
/* MIT License
 *
 * Copyright (c) 2021 Frank Werner-Krippendorf
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef INCLUDED_AARONIA_RTSA_RTSA_HTTP_SERVER_SOURCE_H
#define INCLUDED_AARONIA_RTSA_RTSA_HTTP_SERVER_SOURCE_H

#include <gnuradio/aaronia_rtsa/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace aaronia_rtsa {

    /*!
     * \brief <+description of block+>
     * \ingroup aaronia_rtsa
     *
     */
    class AARONIA_RTSA_API rtsa_http_server_source : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<rtsa_http_server_source> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of aaronia_rtsa::rtsa_http_server_source.
       *
       * To avoid accidental use of raw pointers, aaronia_rtsa::rtsa_http_server_source's
       * constructor is in a private implementation
       * class. aaronia_rtsa::rtsa_http_server_source::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::string, std::string demod_block, std::string spectran_block, float samp_rate, bool tune_spectran_fc, float tune_spectran_fc_offset, float iq_demod_fc);
   
      virtual void set_freq(const uint32_t freq_hz) = 0;
   
    };

  } // namespace aaronia_rtsa
} // namespace gr

#endif /* INCLUDED_AARONIA_RTSA_RTSA_HTTP_SERVER_SOURCE_H */

