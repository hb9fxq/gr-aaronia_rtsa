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

namespace gr
{
  namespace aaronia_rtsa
  {

    rtsa_http_server_source::sptr
    rtsa_http_server_source::make(std::string endpoint, float samp_rate, bool tune_spectran_fc, float tune_spectran_fc_offset, float iq_demod_fc)
    {
      return gnuradio::get_initial_sptr(new rtsa_http_server_source_impl(endpoint, samp_rate, tune_spectran_fc, tune_spectran_fc_offset, iq_demod_fc));
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
      m_spectran_streamer->StartStreamingThread();
      m_samp_rate = samp_rate;
      m_tune_spectran_fc = tune_spectran_fc;
      m_tune_spectran_fc_offset = tune_spectran_fc_offset;
      m_iq_demod_fc = iq_demod_fc;
      //set_output_multiple(16000);
      updateDemod();
    }

    /*
     * Our virtual destructor.
     */
    rtsa_http_server_source_impl::~rtsa_http_server_source_impl()
    {
    }

    void
    rtsa_http_server_source_impl::updateDemod()
    {
      m_spectran_streamer->UpdateDemodulator(m_iq_demod_fc, m_tune_spectran_fc ?  m_tune_spectran_fc_offset: 0e6, (long)m_samp_rate );
    }

    void
    rtsa_http_server_source_impl::set_freq(uint32_t freq_hz)
    {
      m_iq_demod_fc = freq_hz;
      updateDemod();
    }

    int
    rtsa_http_server_source_impl::work(int noutput_items,
                                       gr_vector_const_void_star &input_items,
                                       gr_vector_void_star &output_items)
    {
      unsigned char *out = (unsigned char *)output_items[0];
      return m_spectran_streamer->GetSamples(noutput_items, out);
    }

  } /* namespace aaronia_rtsa */
} /* namespace gr */
