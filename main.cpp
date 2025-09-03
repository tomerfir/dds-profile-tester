#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <dds/core/QosProvider.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <rti/domain/find.hpp>
#include <rti/domain/DomainParticipantConfigParams.hpp>
#include "ThirdParty/tinyxml2.h"
#include "main.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: program <xml1.xml> <xml2.xml> ..." << std::endl;
        std::cout << "Note that it is recommended to test each profile independantly unless they depend on one another, to more easily isolate issues." << std::endl;
        return 1;
    }

    // Check if all files exist
    std::vector<std::string> xml_files;
    for (int i = 1; i < argc; ++i) {
        if (!std::filesystem::exists(argv[i])) {
            std::cout << "File does not exist: " << argv[i] << std::endl;
            return 1;
        }
        xml_files.push_back(argv[i]);
    }

    // Set up QosProvider to load all XML files
    rti::core::QosProviderParams params;
    params.url_profile(xml_files);
    std::unique_ptr<dds::core::QosProvider> provider = nullptr;
    try
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Attempting to load xml files..." << std::endl;
        std::cout << "-------------------------------" << std::endl;
        rti::core::default_qos_provider_params(params);
        provider = std::make_unique<dds::core::QosProvider>(dds::core::QosProvider::Default());
    }
    catch (const std::exception& ex)
    {
        std::cerr << "\nFailed to load one or more of the profile files. exception message (will usually be \"reload profiles\"): " << ex.what() << std::endl;
        std::cerr << "This is usually caused by malformed xml or severe issues in the profile." << std::endl;
        std::cerr << "You should attempt to validate the xml schema, and check for duplicate entity names across multiple profile files." << std::endl;
        std::cerr << "" << std::endl;
        return 1;
    }
    
    std::cout << "------------------------------" << std::endl;
    std::cout << "Successfully loaded xml files." << std::endl;
    std::cout << "------------------------------" << std::endl;

    // Find all participant config names in the XML files
    std::vector<std::string> participant_configs = ExtractParticipantConfigNames(xml_files);

    std::vector<dds::domain::DomainParticipant> participants;
    for (const auto& configName : participant_configs) {
        try {
            std::cout << "------------------------------------------------------" << std::endl;
            std::cout << "Attempting to create the participant: " << configName << std::endl;
            std::cout << "------------------------------------------------------" << std::endl;
            auto participant = provider->extensions().create_participant_from_config(configName);
            participants.push_back(participant);
            std::cout << "--------------------------------------------------------------------" << std::endl;
            std::cout << "Successfully created valid participant from config: " << configName << std::endl;
            std::cout << "--------------------------------------------------------------------" << std::endl;
        }
        catch (const std::exception& ex) {
            std::cout << "--------------------------------------------------------------------" << std::endl;
            std::cout << "Failed to create participant '" << configName << "': " << ex.what() << std::endl;
            std::cout << "--------------------------------------------------------------------" << std::endl;
        }
    }

    // Participants will be cleaned up automatically when they go out of scope
    return 0;
}

/// <summary>
/// Finds all participant config names in the supplied profiles
/// </summary>
/// <param name="xml_files"></param>
/// <returns>List of all participant configs found</returns>
std::vector<std::string> ExtractParticipantConfigNames(dds::core::StringSeq& xml_files)
{
    std::vector<std::string> participant_configs;
    for (const auto& file : xml_files) {
        
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(file.c_str()) != tinyxml2::XML_SUCCESS)
        {
            std::cerr << "Failed to load XML: " << file << ". This is exceedingly strange, since RTI did not pop a parse error from it." << std::endl;
            std::cerr << "Check to see that the xml file is not encoded in an esoteric encoding. Skipping to the next one..." << std::endl;
            continue;
        }

        auto* root = doc.RootElement();
        if (!root) continue;
        for (auto* lib = root->FirstChildElement("domain_participant_library");
            lib != nullptr;
            lib = lib->NextSiblingElement("domain_participant_library")) {
            const char* libName = lib->Attribute("name");
            if (!libName) continue;
            for (auto* participant = lib->FirstChildElement("domain_participant");
                participant != nullptr;
                participant = participant->NextSiblingElement("domain_participant")) {
                const char* participantName = participant->Attribute("name");
                if (!participantName) continue;
                participant_configs.push_back(
                    std::string(libName) + "::" + participantName
                );
            }
        }
    }

    return participant_configs;
}
