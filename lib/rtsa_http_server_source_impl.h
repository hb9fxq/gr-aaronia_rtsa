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

#ifndef INCLUDED_AARONIA_RTSA_RTSA_HTTP_SERVER_SOURCE_IMPL_H
#define INCLUDED_AARONIA_RTSA_RTSA_HTTP_SERVER_SOURCE_IMPL_H

#include <aaronia_rtsa/rtsa_http_server_source.h>
#include <spectranstream.h>

namespace gr {
  namespace aaronia_rtsa {

    class rtsa_http_server_source_impl : public rtsa_http_server_source
    {
     private:

      void updateDemod();

      spectran_stream *m_spectran_streamer;

      float m_samp_rate = 0;
      bool m_tune_spectran_fc; 
      float  m_tune_spectran_fc_offset = 0;
      float m_iq_demod_fc = 0;

     public:
      rtsa_http_server_source_impl(std::string endpoint, float samp_rate, bool tune_spectran_fc, float tune_spectran_fc_offset, float iq_demod_fc);
      ~rtsa_http_server_source_impl();

      void set_freq(const uint32_t freq_hz) override;

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace aaronia_rtsa
} // namespace gr

#endif /* INCLUDED_AARONIA_RTSA_RTSA_HTTP_SERVER_SOURCE_IMPL_H */

