build_dir := "build"
default_config := "Debug"

configure config=default_config:
    cmake -S . -B {{build_dir}} -DCMAKE_BUILD_TYPE={{config}} -DBUILD_TESTING=ON

build config=default_config: (configure config)
    cmake --build {{build_dir}} --config {{config}} --parallel

run config=default_config: (build config)
    cmake --build {{build_dir}} --config {{config}} --target run

test config=default_config: (build config)
    ctest --test-dir {{build_dir}} -C {{config}} --output-on-failure

clean:
    cmake -E remove_directory {{build_dir}}
