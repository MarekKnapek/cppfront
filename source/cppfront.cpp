
//  Copyright (c) Herb Sutter
//  SPDX-License-Identifier: CC-BY-NC-ND-4.0

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


//===========================================================================
//  main - driver
//===========================================================================

#include "to_cpp1.h"

static auto flag_debug_output = false;
static cpp2::cmdline_processor::register_flag cmd_debug(
    9,
    "debug",
    "Emit compiler debug output",
    []{ flag_debug_output = true; }
);

static auto flag_quiet = false;
static cpp2::cmdline_processor::register_flag cmd_quiet(
    9,
    "quiet",
    "Print only error output",
    []{ flag_quiet = true; }
);

auto main_old(
    int   argc,
    char* argv[]
)
    -> int
{
    using namespace cpp2;

    cmdline.set_args(argc, argv);
    cmdline.process_flags();

    if (cmdline.help_was_requested()) {
        return EXIT_SUCCESS;
    }

    if (cmdline.arguments().empty()) {
        return EXIT_FAILURE;
    }

    if (std::filesystem::exists(flag_cwd)) {
        std::filesystem::current_path(flag_cwd);
    }

    //  For each Cpp2 source file
    int exit_status = EXIT_SUCCESS;
    for (auto const& arg : cmdline.arguments())
    {
        if (
            arg.text.starts_with("-")
            || (arg.text.starts_with("/") && !contains(arg.text, '.'))
            )
        {
            auto ambiguous = cmdline.flags_starting_with(arg.text.substr(1));
            if (ambiguous.empty()) {
            }
            else {
                for (auto a : ambiguous) {
                }
            }
            return EXIT_FAILURE;
        }

        cpp2::timer t;
        t.start();

        auto& out = flag_cpp1_filename != "stdout" ? std::cout : std::cerr;

        if (!flag_quiet) {
        }

        //  Load + lex + parse + sema
        cppfront c(arg.text);

        //  Generate Cpp1 (this may catch additional late errors)
        auto count = c.lower_to_cpp1();

        //  If there were no errors, say so and generate Cpp1
        if (c.had_no_errors())
        {
            if (!flag_quiet)
            {
                if (!c.has_cpp1()) {
                }
                else if (c.has_cpp2()) {
                }
                else {
                }

                if (flag_verbose) {
                    auto total = count.cpp1_lines + count.cpp2_lines;
                    auto total_lines = print_with_thousands(total);
                    if (total > 0) {
                        if (count.cpp1_lines == 0) {
                        }
                        else if (count.cpp2_lines / count.cpp1_lines > 25) {
                        }
                        else {
                        }
                    }

                    t.stop();
                    auto total_time = print_with_thousands(t.elapsed().count());

                    std::multimap< long long, std::string_view, std::greater<long long> > sorted_timers;
                    for (auto [name, t] : timers) {
                        sorted_timers.insert({t.elapsed().count(), name});
                    }

                    for (auto [elapsed, name] : sorted_timers) {
                    }
                }

            }
        }
        //  Otherwise, print the errors
        else
        {
            exit_status = EXIT_FAILURE;
        }

        //  And, if requested, the debug information
        if (flag_debug_output) {
        }
    }

    //if (flag_internal_debug) {
    //    stackinstr::print_deepest();
    //    stackinstr::print_largest();
    //}

    return exit_status;
}





#include <vector>

std::vector<unsigned char> g_bytes;

extern "C" int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
    static char const* const s_argv[] = {"cppfront.exe", "test.cpp2"};

    size_t i;
    int argc;
    char** argv;
    std::vector<unsigned char> empty;

    for(i = 0; i != size; ++i)
    {
        if(!(data[i] >= 0x20 && data[i] <= 0x7e))
        {
            return 0;
        }
    }
    g_bytes.insert(g_bytes.cend(), data, data + size);
    argc = 2;
    argv = ((char**)(s_argv));
    main_old(argc, argv);
    swap(g_bytes, empty);
    return 0;
}
