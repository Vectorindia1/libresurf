# MaxMind GeoIP2
-keep class com.maxmind.** { *; }
-dontwarn com.maxmind.**

# Kotlin Serialization
-keepattributes *Annotation*, InnerClasses
-dontnote kotlinx.serialization.AnnotationsKt
-keepclassmembers class kotlinx.serialization.json.** { *** Companion; }
-keepclasseswithmembers class **$$serializer { *; }
-keep @kotlinx.serialization.Serializable class * { *; }

# OkHttp
-dontwarn okhttp3.**
-dontwarn okio.**

# MapLibre
-keep class org.maplibre.** { *; }
-dontwarn org.maplibre.**
