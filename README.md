# Simple Search Engine in C++



## Overview

This C++ project implements a basic search engine. It's designed to index and search a collection of text documents, ranking results based on term frequency. It serves as a foundation for understanding information retrieval concepts.

## Features

-   **Inverted Index:** Efficiently creates an inverted index for fast searching.
-   **Frequency-Based Ranking:** Ranks documents based on the frequency of query terms.
-   **Configurable Data Sources:** Reads data from text files specified in a configuration file.
-   **Basic Request Handling:** Reads search requests from a JSON file.
-   **Output to JSON:** Writes search results to a JSON file.

## Technologies

-   C++
-   CMake
-   nlohmann/json
-   Google Test (for testing)

## Building

1.  **Clone the repository**

    ```bash
    git clone <repository_url>
    cd <repository_directory>
    ```

2.  **Create a build directory**

    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the build with CMake**

    ```bash
    cmake ..
    ```

4.  **Build the project**

    ```bash
    cmake --build .
    ```

## Usage

1.  **Configure the search engine:** Edit the `config.json` file to point to your document files.
2.  **Specify search requests:**  Edit the `requests.json` file to define your search queries.
3.  **Run the executable:** Execute the compiled binary. The executable name may vary depending on your platform and build configuration. It might be something like `search_engine` or `search_engine.exe`.
4.  **View results:** The results are written to the `answers.json` file.

## Configuration Files

The search engine uses two JSON configuration files:

### `config.json`

```json
{
  "config": {
    "name": "Simple Search Engine",
    "version": "1.0",
    "max_responses": 5
  },
  "files": [
    "path/to/document1.txt",
    "path/to/document2.txt"
  ]
}
```
- config: General configuration settings.
- name: Name of the search engine.
- version: Version of the search engine.
- max_responses: The maximum number of search results to return for each query.
- files: A list of paths to the text files that the search engine will index.
### `requests.json`
```json
{
  "requests": [
    "search query 1",
    "another search query"
  ]
}
```


- requests: An array of search queries. Each query is a string.
## Output
### The search results are saved to answers.json in the following format:
```json
{
  "answers": {
    "1": {
      "result": "true",
      "relevance": [
        {
          "docid": 0,
          "rank": 0.8
        },
        {
          "docid": 1,
          "rank": 0.6
        }
      ]
    },
    "2": {
      "result": "false"
    }
  }
}
```

- Each request is assigned a number.
- result: true if any results were found, false otherwise.
- relevance: An array of objects, each containing a docid (the ID of the document) and a rank (the relevance score).
## Testing
- Delete main.cpp from add_executable
- To run the unit tests, use the following command:
```
./search_engine.exe
```

All tests should pass for the project to be considered functional.

## Contributing
Contributions are welcome!
