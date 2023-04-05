template<size_t argument, typename... Ts>
void constructArguments(std::tuple<Ts...> &_arguments, StringVector &&arguments) {
	if constexpr(argument < sizeof...(Ts)) {
		if constexpr(std::is_same<std::tuple_element_t<argument, std::tuple<Ts...>>, int>::value)
			std::get<argument>(_arguments) = stoi(arguments[argument]);
		else
			std::get<argument>(_arguments) = arguments[argument];
		constructArguments<argument + 1, Ts...>(_arguments, std::move(arguments));
	}
}

template<typename T, typename... Ts>
FieldConstructor<T, Ts...>::FieldConstructor(StringVector &&arguments) {
	constructArguments<0, Ts...>(_arguments, std::move(arguments));
}

template<typename T, typename... Ts>
Field * FieldConstructor<T, Ts...>::construct(std::string &&string) const {
	return new T(std::make_from_tuple<T>(std::tuple_cat(std::make_tuple(std::move(string)), _arguments)));
}
