/* -*- c++ -*- */

#define AARONIA_RTSA_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "aaronia_rtsa_swig_doc.i"

%{
#include "aaronia_rtsa/rtsa_http_server_source.h"
%}

%include "aaronia_rtsa/rtsa_http_server_source.h"
GR_SWIG_BLOCK_MAGIC2(aaronia_rtsa, rtsa_http_server_source);
