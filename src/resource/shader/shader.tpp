#pragma once

//---------------------------------------------------------------------------//
//      One Value                                                            //
//---------------------------------------------------------------------------//
template <typename Type>
void Shader::setUniform(const std::string &name, const Type &val1) {
    error("SET", "VAL", "Unrecognized type to set for one value");
}

template <>
inline void Shader::setUniform<int>(const std::string &name, const int &val1) {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), val1);
}

template <>
inline void Shader::setUniform<bool>(const std::string &name, const bool &val1) {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), val1);
}

template <>
inline void Shader::setUniform<float>(const std::string &name, const float &val1) {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), val1);
}

template <>
inline void Shader::setUniform<glm::vec1>(const std::string &name, const glm::vec1 &vec) {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), vec[0]);
}

template <>
inline void Shader::setUniform<glm::vec2>(const std::string &name, const glm::vec2 &vec) {
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), vec[0], vec[1]);
}

template <>
inline void Shader::setUniform<glm::vec3>(const std::string &name, const glm::vec3 &vec) {
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), vec[0], vec[1], vec[2]);
}

template <>
inline void Shader::setUniform<glm::vec4>(const std::string &name, const glm::vec4 &vec) {
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), vec[0], vec[1], vec[2], vec[3]);
}

template <>
inline void Shader::setUniform<glm::mat2>(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

template <>
inline void Shader::setUniform<glm::mat3>(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

template <>
inline void Shader::setUniform<glm::mat4>(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

//---------------------------------------------------------------------------//
//      Two Values                                                           //
//---------------------------------------------------------------------------//
template <typename Type>
void Shader::setUniform(
    const std::string &name,
    const Type &val1,
    const Type &val2
) {
    error("SET", "VAL", "Unrecognized type to set for two values");
}

template <>
inline void Shader::setUniform<int>(
    const std::string &name,
    const int &val1,
    const int &val2
) {
    glUniform2i(glGetUniformLocation(m_id, name.c_str()), val1, val2);
}

template <>
inline void Shader::setUniform<bool>(
    const std::string &name,
    const bool &val1,
    const bool &val2
) {
    glUniform2i(glGetUniformLocation(m_id, name.c_str()), val1, val2);
}

template <>
inline void Shader::setUniform<float>(
    const std::string &name,
    const float &val1,
    const float &val2
) {
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), val1, val2);
}

//---------------------------------------------------------------------------//
//      Three Values                                                         //
//---------------------------------------------------------------------------//
template <typename Type>
void Shader::setUniform(
    const std::string &name,
    const Type &val1,
    const Type &val2,
    const Type &val3
) {
    error("SET", "VAL", "Unrecognized type to set for three values");
}

template <>
inline void Shader::setUniform<int>(
    const std::string &name,
    const int &val1,
    const int &val2,
    const int &val3
) {
    glUniform3i(glGetUniformLocation(m_id, name.c_str()), val1, val2, val3);
}

template <>
inline void Shader::setUniform<bool>(
    const std::string &name,
    const bool &val1,
    const bool &val2,
    const bool &val3
) {
    glUniform3i(glGetUniformLocation(m_id, name.c_str()), val1, val2, val3);
}

template <>
inline void Shader::setUniform<float>(
    const std::string &name,
    const float &val1,
    const float &val2,
    const float &val3
) {
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), val1, val2, val3);
}

//---------------------------------------------------------------------------//
//      Four Values                                                          //
//---------------------------------------------------------------------------//
template <typename Type>
void Shader::setUniform(
    const std::string &name,
    const Type &val1,
    const Type &val2,
    const Type &val3,
    const Type &val4
) {
    error("SET", "VAL", "Unrecognized type to set for four values");
}

template <>
inline void Shader::setUniform<int>(
    const std::string &name,
    const int &val1,
    const int &val2,
    const int &val3,
    const int &val4
) {
    glUniform4i(glGetUniformLocation(m_id, name.c_str()), val1, val2, val3, val4);
}

template <>
inline void Shader::setUniform<bool>(
    const std::string &name,
    const bool &val1,
    const bool &val2,
    const bool &val3,
    const bool &val4
) {
    glUniform4i(glGetUniformLocation(m_id, name.c_str()), val1, val2, val3, val4);
}

template <>
inline void Shader::setUniform<float>(
    const std::string &name,
    const float &val1,
    const float &val2,
    const float &val3,
    const float &val4
) {
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), val1, val2, val3, val4);
}
