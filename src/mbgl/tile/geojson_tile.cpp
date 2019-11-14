#include <mbgl/tile/geojson_tile.hpp>
#include <mbgl/renderer/query.hpp>
#include <mbgl/renderer/tile_parameters.hpp>

namespace mbgl {

GeoJSONTile::GeoJSONTile(const OverscaledTileID& overscaledTileID,
                         std::string sourceID_,
                         const TileParameters& parameters,
                         std::shared_ptr<style::GeoJSONData> data)
    : GeometryTile(overscaledTileID, sourceID_, parameters) {
    updateData(std::move(data), overscaledTileID.canonical);
}

void GeoJSONTile::updateData(std::shared_ptr<style::GeoJSONData> data, CanonicalTileID tileId, bool resetLayers) {
    setData(std::move(data), tileId, resetLayers);
}

void GeoJSONTile::querySourceFeatures(
    std::vector<Feature>& result,
    const SourceQueryOptions& options) {

    // Ignore the sourceLayer, there is only one
    if (auto tileData = getData()) {
        if (auto layer = tileData->getLayer({})) {
            auto featureCount = layer->featureCount();
            for (std::size_t i = 0; i < featureCount; i++) {
                auto feature = layer->getFeature(i);

                // Apply filter, if any
                if (options.filter && !(*options.filter)(style::expression::EvaluationContext { static_cast<float>(this->id.overscaledZ), feature.get() })) {
                    continue;
                }

                result.push_back(convertFeature(*feature, id.canonical));
            }
        }
    }
}

} // namespace mbgl
