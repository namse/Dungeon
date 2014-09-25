#pragma once

const char* SQL_LoginRequest = "SELECT idx FROM players WHERE id=? AND password=?";
const char* SQL_GetPlayerInfo = "SELECT name FROM players WHERE idx=?";
const char* SQL_SignUpRequest = "INSERT INTO players (id, password, name) VALUES (?, ?, ?)";
const char* SQL_IsIDRegisteredRequest = "SELECT COUNT(*) FROM players WHERE id=?";
const char* SQL_IsNameRegisteredRequest = "SELECT COUNT(*) FROM players WHERE name=?";