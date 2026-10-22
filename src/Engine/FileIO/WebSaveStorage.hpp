#pragma once

#include "ISaveStorage.hpp"

#include <nlohmann/json.hpp>

namespace GameEngine::FileIO {

/**
 * Save storage for the browser build. Saves are kept in the page's localStorage
 * so they survive reloads, which the in-memory Emscripten file system does not.
 */
class WebSaveStorage final : public ISaveStorage {
  public:
	WebSaveStorage() = default;
	void write(const nlohmann::json &data) override;
	[[nodiscard]] nlohmann::json read() const override;
	[[nodiscard]] std::vector<SaveMetaData> getSavesData() const override;
	void deleteSaves() override;
	void clearSaveName() override;
	[[nodiscard]] std::string getSaveName() const override;
	void setSaveName(std::string newSaveName) override;
	void deleteCurrentSave() override;

  private:
	std::string saveName{};
};

} // namespace GameEngine::FileIO
