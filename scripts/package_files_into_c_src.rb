File.open("garchinstall.c", "w+") do |c_file|
    File.open("garchinstall.tar.gz") do |gz_file|
        c_file.write("#include \"garchinstall.h\"\n")
        c_file.write("const uint8_t garchinstall[] = \\\n\"")
        i = 0;
        until gz_file.eof?
            buffer = gz_file.read(1)
            if buffer
                if i == 20
                    c_file.write("\"\n\"\\x#{sprintf("%02X", buffer.to_i)}")
                    i = 0
                else
                    c_file.write("\\x#{sprintf("%02X", buffer.to_i)}")
                    i += 1
                end
            end
        end
        c_file.write("\";\n")
    end
end
gz_file_size = File.size("garchinstall.tar.gz")
File.open("garchinstall.h", "w+") do |h_file|
    h_file.write("#include <stdint.h>\n")
    h_file.write("#define GZ_FILE_SIZE #{gz_file_size}\n")
    h_file.write("extern const uint8_t garchinstall[];\n");
end
