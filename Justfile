build_dir := "build"
default_config := "Debug"

configure config=default_config:
    cmake -S . \
        -B {{build_dir}} \
        -DCMAKE_BUILD_TYPE={{config}} \
        -DBUILD_TESTING=ON

build config=default_config: (configure config)
    cmake \
        --build {{build_dir}} \
        --config {{config}} \
        --parallel

run config=default_config: (build config)
    cmake --build {{build_dir}} \
        --config {{config}} \
        --target run

[arg("verbose", long, short="v", value="--verbose")]
[arg("regex", long, short="r", value=".*")]
test config=default_config verbose="" regex=".*": (configure config)
    cmake --build {{build_dir}} \
        --config {{config}} \
        --target dreamy_chip8_tests \
        --parallel

    ctest --test-dir {{build_dir}} \
        -C {{config}} \
        --output-on-failure \
        --tests-regex {{regex}} \
        {{verbose}}

clean:
    cmake -E remove_directory {{build_dir}}
