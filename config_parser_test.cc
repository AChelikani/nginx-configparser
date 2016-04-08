#include "gtest/gtest.h"
#include "config_parser.h"
#include <sstream>
#include <string>


TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

TEST(NginxConfigParserTest, EventsConfig) {
	NginxConfigParser parser;
	NginxConfig out_config;

	bool success = parser.Parse("events_config", &out_config);

	EXPECT_TRUE(success);	
}

// Has nested elements
TEST(NginxConfigParserTest, WordpressConfig) {
	NginxConfigParser parser;
	NginxConfig out_config;
	bool success = parser.Parse("wordpress_config", &out_config);

	EXPECT_TRUE(success);			
}

// Bare bones, with http, server, location, if statement
TEST(NginxConfigParserTest, BarebonesConfig) {
	NginxConfigParser parser;
	NginxConfig out_config;
	bool success = parser.Parse("barebones_config", &out_config);

	EXPECT_TRUE(success);			
}

// Consecutive nested braces
TEST(NginxConfigParserTest, LocationConfig) {
	NginxConfigParser parser;
	NginxConfig out_config;
	bool success = parser.Parse("location_config", &out_config);

	EXPECT_TRUE(success);			
}

// Tesing for false configuration
TEST(NginxConfigParserTest, InvalidConfig) {
	NginxConfigParser parser;
	NginxConfig out_config;
	bool success = parser.Parse("invalid_config", &out_config);

	EXPECT_FALSE(success);			
}

class NginxStringConfigTest : public ::testing::Test {
protected:
	bool ParseString(const std::string& config_string) {
		std::stringstream config_stream(config_string);
		return parser_.Parse(&config_stream,  &out_config_);
	}
	NginxConfigParser parser_;
	NginxConfig out_config_;
};

// Testing using class
TEST_F(NginxStringConfigTest, BasicParsing) {
	EXPECT_TRUE(ParseString("server { server info here; }"));
	EXPECT_EQ(1, out_config_.statements_.size());
}

// Testing  tostring method
TEST(NginxConfigTest, ToString) {
	NginxConfigStatement statement;
	statement.tokens_.push_back("listen");
	statement.tokens_.push_back("80");
	EXPECT_EQ("listen 80;\n", statement.ToString(0));
}