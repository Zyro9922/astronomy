/*=============================================================================
Copyright 2020 Gopi Krishna Menon <krishnagopi487.github@outlook.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_TEST_MODULE hdu_test

#include <boost/astronomy/io/hdu.hpp>
#include <boost/test/unit_test.hpp>
#include <map>

class hdu_fixture {
  const std::string samples_directory =
      std::string(SOURCE_DIR) + "/fits_sample_files/";
  std::map<std::string, std::fstream> sample_files;

 public:
  hdu_fixture() {
    // Any file additions or deletions should be made here only

    // Contains only primary_hdu
    sample_files.emplace("primary_hdu",
                         samples_directory + "fits_sample1.fits");

    // Points to ASCII hdu
    std::fstream ascii_file(samples_directory + "fits_sample2.fits");
    ascii_file.seekg(2880);  // Points to ASCII hdu
    sample_files.emplace("ascii_hdu", std::move(ascii_file));
  }

  std::fstream& get_hdu_filestream(const std::string& hdu_name) {
    return sample_files[hdu_name];
  }
};

using namespace boost::astronomy::io;

BOOST_AUTO_TEST_SUITE(hdu_constructors)


BOOST_FIXTURE_TEST_CASE(read_header_from_filestream, hdu_fixture) {
  hdu temp_hdu;
  temp_hdu.read_header(get_hdu_filestream("primary_hdu"));

  BOOST_REQUIRE_EQUAL(temp_hdu.card_count(), 262);
}


BOOST_FIXTURE_TEST_CASE(read_header_from_filestream_specific_pos, hdu_fixture) {
  hdu temp_hdu;
  temp_hdu.read_header(get_hdu_filestream("ascii_hdu"));

  BOOST_REQUIRE_EQUAL(temp_hdu.card_count(), 105);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(hdu_methods)

BOOST_FIXTURE_TEST_CASE(bitpix_func, hdu_fixture) {
  hdu hdu1(get_hdu_filestream("primary_hdu"));
  hdu hdu2(get_hdu_filestream("ascii_hdu"));

  BOOST_CHECK_MESSAGE(hdu1.bitpix() == bitpix::_B32,
                      "The bitpix values do not match");
  BOOST_CHECK_MESSAGE(hdu2.bitpix() == bitpix::B8,
                      "The bitpix values do not match");
}
BOOST_FIXTURE_TEST_CASE(total_dimensions, hdu_fixture) {
  hdu hdu1(get_hdu_filestream("primary_hdu"));
  hdu hdu2(get_hdu_filestream("ascii_hdu"));

  BOOST_REQUIRE_EQUAL(hdu1.total_dimensions(), 3);
  BOOST_REQUIRE_EQUAL(hdu2.total_dimensions(), 2);
}

BOOST_FIXTURE_TEST_CASE(naxis_n, hdu_fixture) {
  hdu hdu1(get_hdu_filestream("primary_hdu"));
  hdu hdu2(get_hdu_filestream("ascii_hdu"));

  BOOST_REQUIRE_EQUAL(hdu1.naxis(1), 200);
  BOOST_REQUIRE_EQUAL(hdu1.naxis(2), 200);
  BOOST_REQUIRE_EQUAL(hdu1.naxis(3), 4);

  BOOST_REQUIRE_EQUAL(hdu2.naxis(1), 52);
  BOOST_REQUIRE_EQUAL(hdu2.naxis(2), 1455);
}

BOOST_FIXTURE_TEST_CASE(value_of, hdu_fixture) {
  hdu test_header1(get_hdu_filestream("primary_hdu"));
  hdu test_header2(get_hdu_filestream("ascii_hdu"));

  BOOST_REQUIRE_EQUAL(test_header2.value_of<std::string>("AUTHOR"),
                      "Acker et al.");
  BOOST_REQUIRE_EQUAL(test_header1.value_of<std::string>("CTYPE2"),
                      "DEC--TAN");
  BOOST_REQUIRE_EQUAL(test_header2.value_of<int>("TBCOL5"), 20);
  BOOST_REQUIRE_EQUAL(test_header1.value_of<int>("GPIXELS"), 632387);
  BOOST_REQUIRE_EQUAL(test_header1.value_of<double>("PHOTFLAM"), 3.44746E-16);
  BOOST_REQUIRE_EQUAL(test_header1.value_of<double>("MEANC100"), 0.3916293);
}

BOOST_FIXTURE_TEST_CASE(set_unit_end, hdu_fixture) {
  // TODO : Write test to check its handling against faliure as well
  hdu test;
  auto& sample = get_hdu_filestream("ascii_hdu");

  sample.seekg(0);
  test.set_unit_end(sample);

  BOOST_REQUIRE_EQUAL(sample.tellg(), 2880);
}
BOOST_FIXTURE_TEST_CASE(card_count, hdu_fixture) {
  hdu hdu1(get_hdu_filestream("primary_hdu"));
  hdu hdu2(get_hdu_filestream("ascii_hdu"));

  BOOST_REQUIRE_EQUAL(hdu1.card_count(), 262);
  BOOST_REQUIRE_EQUAL(hdu2.card_count(), 105);
}
BOOST_AUTO_TEST_SUITE_END()
