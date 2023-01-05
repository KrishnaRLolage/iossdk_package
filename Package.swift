// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "DragonMedicalSpeechKit",
    platforms: [
        .iOS(.v14)
        ],
    products: [
        // Products define the executables and libraries produced by a package, and make them visible to other packages.
        .library(
            name: "DragonMedicalSpeechKit",
            targets: ["DragonMedicalSpeechKitLib"]
        )
    ],
    dependencies: [
            // Dependencies declare other packages that this package depends on.
            .package(
              name: "YbridOpus",
              url: "https://github.com/ybrid/opus-swift.git",
              from: "0.8.0")
        ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages which this package depends on.
        .target(
            name: "DragonMedicalSpeechKitLib",
            dependencies: [.target(name: "DragonMedicalSpeechKit"), .product(name: "YbridOpus", package: "YbridOpus")],
            path: "Sources/SDK"
        ),
        .binaryTarget(
                    name: "DragonMedicalSpeechKit",
                    path: "Sources/SDK/DragonMedicalSpeechKit.zip"
                )
    ]
)

