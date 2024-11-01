#include <iostream>
#include <fstream>
#include <json/json.h>

void deleteAndWriteHtml(const std::string& fileName) {
    std::ofstream outFile(fileName);
    outFile << R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Document</title>
            <link rel="stylesheet" href="css/under_inventory.css">
        </head>
        <body>
        <script src="js/equipment_item.js">
            
        </script>
            <div class="container">
                <div class="main">
                    <div class="inventory">
                    </div>
                </div>
            </div>
        </body>
        </html>
    )";
    outFile.close();
}

void replaceLine(const std::string& fileName, int lineNum, const std::string& text) {
    std::ifstream inFile(fileName);
    std::vector<std::string> lines;
    std::string line;

    // Read all lines from the file
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    // Modify the specified line
    if (lineNum >= 0 && lineNum < static_cast<int>(lines.size())) {
        lines[lineNum] = text;
    } else {
        std::cerr << "Invalid line number: " << lineNum << std::endl;
        return;
    }

    // Write modified lines back to the file
    std::ofstream outFile(fileName);
    for (const auto& modifiedLine : lines) {
        outFile << modifiedLine << '\n';
    }
}

int main() {
    // Replace with your JSON file path
    const std::string jsonFilePath = "../json/player_data.json";
    
    // Replace with your HTML file path
    const std::string htmlFileName = "helmet_equipment.html";

    deleteAndWriteHtml(htmlFileName);

    Json::Value data;
    std::ifstream jsonFile(jsonFilePath);
    jsonFile >> data;
    jsonFile.close();

    std::string item = "";
    std::ifstream htmlFile(htmlFileName);
    std::vector<std::string> lines;
    std::string line;

    // Read all lines from the HTML file
    while (std::getline(htmlFile, line)) {
        lines.push_back(line);
    }

    htmlFile.close();

    if (i["type"].asString() == "helmet_equipment"){
        for (const auto& i : data["inventory"]) {
            item += 
                (<!-- "i["name"].asString()"-->
                <div id="i["name"] + i["defense"]">
                    <button onclick="equip("i["name"], i["defense"]" id="invenory_object">
                        <img id="img" src="images/items/" + )"i["name"].asString() +.png" style="float: left; margin-left: 10px; height: 50px; width: 50px; margin-top: 40px;">
                        <p id="title-entity"> i["name"].asString() </p>
                        <p id="desc"> i["description"].asString() </p>
                        <p id="stock">)i["number"].asString() </p>
                    </button>
                </div>
            )";

            replaceLine(htmlFileName, 14, item);
            item = "";
            }
    }
    std::cout << "Process done." << std::endl;

    return 0;
}
