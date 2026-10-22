#include "Engine/FileIO/WebSaveStorage.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <memory>
#include <stdexcept>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <cstdlib>

// Each save is stored under "coredumpcastle.save.<name>" as {"savedAt": <ms since epoch>, "data": <json string>}.
// The JS helpers return malloc'ed strings (or null); the caller must free() them.

// clang-format off
EM_JS(void, ccastle_store_save, (const char *name, const char *json), {
	const entry = {savedAt : Date.now(), data : UTF8ToString(json)};
	localStorage.setItem("coredumpcastle.save." + UTF8ToString(name), JSON.stringify(entry));
});

EM_JS(char *, ccastle_load_save, (const char *name), {
	const raw = localStorage.getItem("coredumpcastle.save." + UTF8ToString(name));
	if (raw === null)
		return 0;
	return stringToNewUTF8(JSON.parse(raw).data);
});

EM_JS(char *, ccastle_list_saves, (), {
	const saves = [];
	const prefix = "coredumpcastle.save.";
	for (let i = 0; i < localStorage.length; ++i) {
		const key = localStorage.key(i);
		if (!key.startsWith(prefix))
			continue;
		try {
			saves.push({name : key.substring(prefix.length), savedAt : JSON.parse(localStorage.getItem(key)).savedAt});
		} catch (e) {
		}
	}
	return stringToNewUTF8(JSON.stringify(saves));
});

EM_JS(void, ccastle_delete_save, (const char *name), {
	localStorage.removeItem("coredumpcastle.save." + UTF8ToString(name));
});
// clang-format on
#endif

namespace GameEngine::FileIO {

namespace {
#ifdef __EMSCRIPTEN__
struct MallocDeleter {
	void operator()(char *p) const { std::free(p); }
};
using JsString = std::unique_ptr<char, MallocDeleter>;
#endif

[[nodiscard]] std::filesystem::file_time_type fromUnixMillis(const std::int64_t millis)
{
	// Only used for display and ordering; SaveGameFormatter converts back relative to "now".
	const auto sysTime = std::chrono::system_clock::time_point{std::chrono::milliseconds{millis}};
	const auto offset = sysTime - std::chrono::system_clock::now();
	return std::filesystem::file_time_type::clock::now()
	       + std::chrono::duration_cast<std::filesystem::file_time_type::duration>(offset);
}
} // namespace

void WebSaveStorage::write(const nlohmann::json &data)
{
	if (saveName.empty())
		throw std::runtime_error("Cannot write save without a save name");
#ifdef __EMSCRIPTEN__
	ccastle_store_save(saveName.c_str(), data.dump().c_str());
#else
	(void)data;
	throw std::runtime_error("WebSaveStorage is only available in the browser build");
#endif
}

nlohmann::json WebSaveStorage::read() const
{
	if (saveName.empty())
		return nlohmann::json::object(); // empty json to skip reinitialization
#ifdef __EMSCRIPTEN__
	const JsString raw{ccastle_load_save(saveName.c_str())};
	if (!raw)
		throw std::runtime_error("Save '" + saveName + "' does not exist");
	return nlohmann::json::parse(raw.get());
#else
	throw std::runtime_error("WebSaveStorage is only available in the browser build");
#endif
}

std::vector<SaveMetaData> WebSaveStorage::getSavesData() const
{
	std::vector<SaveMetaData> savesMetaData;
#ifdef __EMSCRIPTEN__
	const JsString raw{ccastle_list_saves()};
	for (const auto &entry : nlohmann::json::parse(raw.get())) {
		savesMetaData.emplace_back(entry.at("name").get<std::string>(), fromUnixMillis(entry.at("savedAt").get<std::int64_t>()));
	}
	std::ranges::sort(savesMetaData,
	                  [](const SaveMetaData &a, const SaveMetaData &b) { return a.lastSaved > b.lastSaved; });
#endif
	return savesMetaData;
}

void WebSaveStorage::deleteSaves()
{
#ifdef __EMSCRIPTEN__
	for (const auto &save : getSavesData())
		ccastle_delete_save(save.saveName.c_str());
#endif
}

void WebSaveStorage::clearSaveName()
{
	saveName.clear();
}

std::string WebSaveStorage::getSaveName() const
{
	return saveName;
}

void WebSaveStorage::setSaveName(std::string newSaveName)
{
	saveName = std::move(newSaveName);
}

void WebSaveStorage::deleteCurrentSave()
{
#ifdef __EMSCRIPTEN__
	if (!saveName.empty())
		ccastle_delete_save(saveName.c_str());
#endif
	clearSaveName();
}

} // namespace GameEngine::FileIO
