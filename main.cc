#include <cmath>
#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include<string>
#include "rapidcsv.h"
int main()
{
    rapidcsv::Document doc{
        "titanic.csv",
        rapidcsv::LabelParams{},
        rapidcsv::SeparatorParams{},
        rapidcsv::ConverterParams{true}};

    /*reading column data from csv file*/
    std::vector<int> Survived{doc.GetColumn<int>("Survived")};
    std::vector<std::string> Name{doc.GetColumn<std::string>("Name")};
    std::vector<std::string> sex{doc.GetColumn<std::string>("Sex")};
    std::vector<double> age{doc.GetColumn<double>("Age")};
    std::vector<int> pclass{doc.GetColumn<int>("Pclass")};

    /*removing qutoes from string "females" / "males" 
    for (std::string &item : sex)
    {
        item.erase(0, 1);
        item.pop_back();
    };
    */
    /*
        displaying first five rows
    */
    std::cout << "\nFirst 5 rows data : \n"
              << "survived" << std::setw(25) << "sex" << std::setw(25) << "age" << std::setw(25) << "pclass\n";
    for (size_t i{0}; i < 5; ++i)
    {
        std::cout << std::setw(7) << Survived.at(i) << std::setw(25) << sex.at(i) << std::setw(25) << age.at(i) << std::setw(25) << pclass.at(i) << "\n";
    };

    /*displaying last five rows data*/
    std::cout << "\nlast 5 rows data :\n "
              << "survived" << std::setw(25) << "sex" << std::setw(25) << "age" << std::setw(25) << "pclass\n";
    for (size_t i{doc.GetRowCount() - 5}; i < doc.GetRowCount(); ++i)
    {
        std::cout << std::setw(7) << Survived.at(i) << std::setw(25) << sex.at(i) << std::setw(25) << age.at(i) << std::setw(25) << pclass.at(i) << "\n";
    };

    // /*remove NaN Value from age vector*/
    auto v_removeNaN = age | std::views::filter([](double &value)
                                                { return std::isnan(value) == false; });
    std::vector<double> CleanAge{std::begin(v_removeNaN), std::end(v_removeNaN)};

    std::sort(std::begin(CleanAge), std::end(CleanAge));
    /*median value if size of age vector is even*/
    double median{};
    if (CleanAge.size() % 2 == 0)
    {
        median = (CleanAge.at((CleanAge.size() / 2 - 1) + CleanAge.at(CleanAge.size() / 2)) / 2);
    }
    else
    {
        median = CleanAge.at(CleanAge.size() / 2);
    };

    std::cout << "\nPassenger with Age data  :" << CleanAge.size() << "\n";
    std::cout << "Average Age : " << std::accumulate(std::begin(CleanAge), std::end(CleanAge), 0.0) / CleanAge.size() << "\n";
    std::cout << "Minimum Age : " << CleanAge.front() << "\n";
    std::cout << "Maximum Age : " << CleanAge.back() << "\n";
    std::cout << "Median Age  : " << median << "\n";

    return 0;
}