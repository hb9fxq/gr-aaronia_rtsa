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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "rtsa_http_server_source_impl.h"

namespace gr {
  namespace aaronia_rtsa {

    rtsa_http_server_source::sptr
    rtsa_http_server_source::make(std::string endpoint, float samp_rate, bool tune_spectran_fc, float tune_spectran_fc_offset, float iq_demod_fc)
    {
      return gnuradio::get_initial_sptr
        (new rtsa_http_server_source_impl(endpoint, samp_rate, tune_spectran_fc, tune_spectran_fc_offset, iq_demod_fc));
    }


    /*
     * The private constructor
     */
    rtsa_http_server_source_impl::rtsa_http_server_source_impl(std::string endpoint, float samp_rate, bool tune_spectran_fc, float tune_spectran_fc_offset, float iq_demod_fc)
      : gr::sync_block("rtsa_http_server_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      m_spectran_streamer = new spectran_stream(spectran_stream::STREAMER_TYPE::QUEUED_CF32, endpoint);
      m_spectran_streamer->UpdateDemodulator(iq_demod_fc, tune_spectran_fc?tune_spectran_fc_offset:0e6 ,samp_rate);
      m_spectran_streamer->StartStreamingThread();


            
    }

    /*
     * Our virtual destructor.
     */
    rtsa_http_server_source_impl::~rtsa_http_server_source_impl()
    {
    }

    int
    rtsa_http_server_source_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      gr_complex *out = (gr_complex *)output_items[0];
      m_spectran_streamer->GetSamples(noutput_items, out);
      return noutput_items;
    }

  } /* namespace aaronia_rtsa */
} /* namespace gr */

