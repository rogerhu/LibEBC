#include "ebc/util/Xml.h"

#include "catch.hpp"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>

using namespace ebc;

TEST_CASE("Xml Helper", "[XmlHelper]") {
  xmlDoc* doc = xmlNewDoc(BAD_CAST "1.0");
  xmlNode* root = xmlNewNode(nullptr, BAD_CAST "root");

  xmlNode* node1 = xmlNewChild(root, nullptr, BAD_CAST "node1", BAD_CAST "content1");

  SECTION("GetContent") {
    REQUIRE("content1" == util::xml::GetContent(node1));
  }

  xmlNode* node2 = xmlNewNode(nullptr, BAD_CAST "node2");
  xmlAddChild(root, node2);

  SECTION("FindNodeWithName") {
    REQUIRE(node1 == util::xml::FindNodeWithName(root, "node1"));
    REQUIRE(node2 == util::xml::FindNodeWithName(root, "node2"));
  }

  xmlNode* child1 = xmlNewChild(node2, nullptr, BAD_CAST "child", BAD_CAST "child1");
  xmlNode* child2 = xmlNewChild(node2, nullptr, BAD_CAST "child", BAD_CAST "child2");
  xmlNode* child3 = xmlNewChild(node2, nullptr, BAD_CAST "child", BAD_CAST "child3");

  SECTION("FindNodeWithNameAndContent") {
    REQUIRE(child1 == util::xml::FindNodeWithNameAndContent(root, "child", "child1"));
    REQUIRE(child2 == util::xml::FindNodeWithNameAndContent(root, "child", "child2"));
    REQUIRE(child3 == util::xml::FindNodeWithNameAndContent(root, "child", "child3"));
  }

  SECTION("GetTextFromNodesWithName") {
    std::vector<std::string> expected = {"child1", "child2", "child3"};
    REQUIRE(expected == util::xml::GetTextFromNodesWithName(node2->children, "child"));
  }

  xmlFreeDoc(doc);
}
